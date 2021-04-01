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

template <typename Task>
class ThreadPool
{
public:
    ThreadPool(int worker_num, int max_cap)
    {
        this->worker_num = worker_num;
        // this->task_num = 0;
        this->sprites_.resize(worker_num);
        this->idx.store(-1);
        this->max_cap = max_cap;
        this->tasks_.resize(max_cap);
        flags_ = std::vector<std::atomic<bool>>(max_cap);
        for (int i = 0; i < max_cap; i++)
        {
            // flags_.push_back(std::atomic<bool>());
            flags_[i].store(false);
        }
        stopped.store(false);
        created_worker = 0;
        finished_jobs.store(0);
        // now set those tiny sprites free
        // sprites_ = std::vector<std::thread>(worker_num, )
        for (int i = 0; i < worker_num; i++)
        {
            auto&& t = std::thread(std::bind(spawn_sprite, this));
            sprites_[i] = std::move(t);
            // sprites_[i].detach();
            created_worker++;
            // std::cout << "worker no." << created_worker << " create done" << std::endl;
        }
        std::cout<<"size of sprites:"<<sprites_.size()<<std::endl;
    }
    ~ThreadPool() = default;

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
        while (!stopped.load())
        {
            if (thread_pool->idx.load() < 0)
            {
                // std::cout << "sleep of spawn_sprite" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
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
                // std::cout<<"job index:"<<c_idx+1<<std::endl;
                (*one_job)();
                thread_pool->flags_[c_idx+1].store(false);
                // thread_pool->tasks_.pop_back();
            }
            finished_jobs.fetch_add(1);
            // std::cout << finished_jobs.load() << " do job once :" << std::endl;
        }
        std::cout<<"sprite break"<<std::endl;
    }

    void stop()
    {
        stopped.store(true);
        std::cout<<"finished jobs:"<<finished_jobs.load()<<std::endl;
        std::cout<<"size of sprites when stop:"<<sprites_.size()<<std::endl;
        for (auto &t : sprites_)
        {
            t.join();
            std::cout<<"sprite fly away"<<std::endl;
        }
        tasks_.clear();
        std::cout<<"task cleared"<<std::endl;
    }

private:
    std::vector<std::thread> sprites_;
    std::vector<std::atomic<bool>> flags_;
    std::vector<Task> tasks_;
    int worker_num;
    // int task_num;
    int max_cap;
    std::atomic<int> idx;
};