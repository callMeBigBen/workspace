#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <unordered_set>
#include <sstream> // for ostringstream

static std::mutex task_mut;
static std::atomic<bool> stopped;
static int created_worker;
static std::atomic<int> finished_jobs;


template <typename Task>
class ThreadPool
{
public:
    ThreadPool(int worker_num, int max_cap)
    {
        this->worker_num = worker_num;
        this->sprites_.resize(worker_num);
        this->idx.store(-1);
        this->max_cap = max_cap;
        this->tasks_.resize(max_cap);
        stopped.store(false);
        created_worker = 0;
        finished_jobs.store(0);
        for (int i = 0; i < worker_num; i++)
        {
            auto&& t = std::thread(std::bind(spawn_sprite, this));
            sprites_[i] = std::move(t);
            created_worker++;
        }
    }
    ~ThreadPool() = default;

    bool async_enqueue(Task &&r)
    {
        if (idx.load() + 1 >= max_cap){
            std::ostringstream out;  
            out<<"one task throwed"<<std::endl;
            std::cout<<out.str();
            return false;
        }
        // dispatch jobs to those cuties sprites.
        std::lock_guard<std::mutex> lock(task_mut);
        auto p_idx = idx.fetch_add(1);
        tasks_[p_idx+1] = std::forward<Task &&>(r);
        return true;
    }

    static void spawn_sprite(ThreadPool *thread_pool)
    {
        while (!stopped.load())
        {
            Task *one_job;
            {
                // double check before entering critical section, in order to avoid race condition
                if(thread_pool->idx.load() < 0){
                    std::this_thread::sleep_for(std::chrono::microseconds(10));
                    continue;
                }
                
                std::lock_guard<std::mutex> lock(task_mut);
                if(thread_pool->idx.load() < 0){
                    continue;
                }
                // this tiny sprite got a real job.
                auto c_idx = thread_pool->idx.fetch_sub(1);  
                one_job = &thread_pool->tasks_[c_idx];
            }
            (*one_job)(); // do job without holding the mutex
            finished_jobs.fetch_add(1);
        }
    }

    void stop()
    {
        stopped.store(true);
        std::cout<<"finished jobs:"<<finished_jobs.load()<<std::endl;
        for (auto &t : sprites_)
        {
            t.join();
        }
        tasks_.clear();
    }

private:
    std::vector<std::thread> sprites_;
    std::vector<std::atomic<bool>> flags_;
    std::vector<Task> tasks_;
    int worker_num;
    int max_cap;
    std::atomic<int> idx;
};