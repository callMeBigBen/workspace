#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <unordered_set>

static std::mutex task_mut;
static std::atomic<bool> stopped;
static int created_worker;
static std::atomic<int> finished_jobs;
static std::unordered_set<int> set;

template <typename Task>
class ThreadPool
{
public:
    ThreadPool(int worker_num, int max_cap)
    {
        this->worker_num = worker_num;
        // this->task_num = 0;
        this->sprites_.reserve(worker_num);
        this->idx.store(-1);
        this->max_cap = max_cap;
        this->tasks_.resize(max_cap);
        this->flags_ = std::vector<std::atomic<bool>>(max_cap);
        for (int i = 0; i < max_cap; i++)
        {
            // this->flags_.push_back(std::atomic<bool>());
            this->flags_[i].store(false);
        }
        stopped.store(false);
        created_worker = 0;
        finished_jobs.store(0);
        set = std::unordered_set<int>();
        // now set those tiny sprites free
        for (int i = 0; i < worker_num; i++)
        {
            sprites_[i] = std::move(std::thread(std::bind(spawn_sprite, this)));
            // sprites_[i].detach();
            created_worker++;
            // std::cout << "worker no." << created_worker << " create done" << std::endl;
        }
    }
    ~ThreadPool()
    {
        stop();
    }

    void async_enqueue(Task &&r)
    {
        if (idx.load() + 1 >= max_cap)
            return;
        // std::lock_guard<std::mutex> l(task_mut);
        // dispatch jobs for those cuties.
        auto p_idx = idx.fetch_add(1);
        tasks_[p_idx] = std::forward<Task &&>(r);
        flags_[p_idx].store(true);
    }

    static void spawn_sprite(ThreadPool *thread_pool)
    {
        while (true)
        {
            if (stopped.load())
                break;
            while (thread_pool->idx.load() < 0)
            {
                // std::cout << "sleep of spawn_sprite" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            {
                // std::lock_guard<std::mutex> l(task_mut);
                // this tiny sprite got a job.
                Task *one_job;
                auto c_idx = thread_pool->idx.fetch_sub(1);
                if(c_idx < 0) continue;                
                while (!thread_pool->flags_[c_idx+1].load())
                    continue;
                one_job = &thread_pool->tasks_[c_idx+1];
                std::cout<<"job index:"<<c_idx+1<<std::endl;
                if(set.count(c_idx+1) > 0){
                    std::cout<<"found dup!"<<std::endl;
                }
                set.insert(c_idx+1);
                (*one_job)();
                thread_pool->flags_[c_idx+1].store(false);
                // thread_pool->tasks_.pop_back();
            }
            finished_jobs.fetch_add(1);
            // std::cout << finished_jobs.load() << " do job once :" << std::endl;
        }
    }

    void stop()
    {
        stopped.store(true);
        for (auto &t : sprites_)
        {
            t.join();
        }
    }

private:
    std::vector<std::thread> sprites_;
    std::vector<Task> tasks_;
    std::vector<std::atomic<bool>> flags_;
    int worker_num;
    // int task_num;
    int max_cap;
    std::atomic<int> idx;
};