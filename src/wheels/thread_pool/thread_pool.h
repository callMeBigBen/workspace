#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <unordered_set>
#include <sstream> // for ostringstream
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/**
 * data structures for synchronization and debug.
 */
// static std::mutex task_mut;
static std::atomic<bool> stopped;
static size_t created_worker;
static std::atomic<size_t> finished_jobs;

template <typename Task>
class ThreadPool
{
public:
    ThreadPool(size_t worker_num, size_t buffer_size = 1024) // 1024 is the heuristic value of buffer_size
    {
        if (worker_num <= 0 || buffer_size <= 0)
        {
            printf("wrong arguments. worker_num:%lu, buffer_size:%lu", worker_num, buffer_size);
            exit(0);
        }
        this->worker_num = worker_num;
        this->sprites_.resize(worker_num);
        this->p_idx.store(-1);
        this->c_idx.store(-1);
        this->buffer_size = buffer_size;
        this->tasks_.resize(buffer_size);
        this->flags_ = std::vector<std::atomic<bool> >(buffer_size);
        for (auto &flag : this->flags_)
        {
            flag.store(true);
        }
        stopped.store(false);
        created_worker = 0;
        finished_jobs.store(0);
        for (size_t i = 0; i < worker_num; i++)
        {
            auto &&t = std::thread(std::bind(spawn_sprite, this));
            sprites_[i] = std::move(t);
            created_worker++;
        }
    }
    ~ThreadPool() = default;

    bool async_enqueue(Task &&r)
    {
        /**
         * overview of task enqueue
         * 1. check whether the p_idx (AKA, the next producible slot) has been consumed. 
         * 2. if no, throw the taks and return a false
         * 3. if yes, preempt this p_idx and increment it by 1
         * 4. and then pust the task to tasks_[(p_idx-1)%buffer_size]
         */
        // the next slot has not been consumed. We cannot add any more task.

        size_t cur_p_idx; // keep track of cur p_idx
        if (flags_[(cur_p_idx = p_idx.fetch_add(1)) % buffer_size].load() == false)
        {
            p_idx.fetch_sub(1);
            std::ostringstream out;
            out << "one task throwed" << std::endl;
            std::cout << out.str();
            return false;
        }

        tasks_[cur_p_idx % buffer_size] = std::forward<Task &&>(r);
        flags_[cur_p_idx % buffer_size].store(false);
        return true;
    }

    static void spawn_sprite(ThreadPool *thread_pool)
    {
        while (!stopped.load())
        {
            size_t cur_c_idx; // keep track of cur c_idx
            if (thread_pool->flags_[(cur_c_idx = thread_pool->c_idx.fetch_add(1)) % thread_pool->buffer_size].load() == true)
            {
                thread_pool->c_idx.fetch_sub(1);
                continue;
            }
            Task &&one_job = move(thread_pool->tasks_[cur_c_idx % thread_pool->buffer_size]);
            thread_pool->flags_[cur_c_idx % thread_pool->buffer_size].store(true);
            // {
            //     // double check before entering critical section, in order to avoid race condition
            //     if(thread_pool->idx.load() < 0){
            //         std::this_thread::sleep_for(std::chrono::microseconds(10));
            //         continue;
            //     }

            //     std::lock_guard<std::mutex> lock(task_mut);
            //     if(thread_pool->idx.load() < 0){
            //         continue;
            //     }
            //     // this tiny sprite got a real job.
            //     c_idx = thread_pool->idx.fetch_sub(1);
            //     one_job = thread_pool->tasks_[c_idx];
            // }
            one_job(); // do job without holding the mutex
            // thread_pool->flags_[c_idx].store(true);
            finished_jobs.fetch_add(1);
        }
    }

    void stop()
    {
        stopped.store(true);
        std::cout << "finished jobs:" << finished_jobs.load() << std::endl;
        for (auto &t : sprites_)
        {
            t.join();
        }
        tasks_.clear();
    }

private:
    /**
     * data structures for the asynchronous executor.
     * 1. sprites_: the vector to hold the reference to threads
     * 2. tasks_: a vector-based RingBuffer to hold all tasks
     * 3. flags_: also, a vector-based RingBuffer, to represent the consuption status of each slot
     * 4. worker_num: the number of threads
     * 5. buffer_size: the size of the RingBuffer
     * 6. c_idx: current consuption idx of the RingBuffer
     * 7. p_idx: current product idx of RingBuffer
     */
    std::vector<std::thread> sprites_;
    std::vector<Task> tasks_;
    std::vector<std::atomic<bool> > flags_; // whether the slot has been consumed
    size_t worker_num;
    size_t buffer_size;
    std::atomic<size_t> c_idx;
    std::atomic<size_t> p_idx;
};