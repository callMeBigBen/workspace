#include <thread>
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <functional>
#include <pthread.h>

class ThreadPool {
public:
    ~ThreadPool() = default;
    ThreadPool(size_t max_queue_size = 100){
        for(int i=0;i < max_queue_size;++i){
            auto thread = std::make_shared<std::thread>();
            idle_list.push_back(thread);
        }
    }
    
    void add_job(std::function<void()>&& func){
        job_list.push_back(std::move(func));
    }

    void start(){
        while(job_list.size() > 0 && idle_list.size() > 0){
            auto thread = idle_list.front();
            idle_list.pop_front();
            thread->
        } 
    }
private:
    std::list<std::function<void()>> job_list;
    std::list<std::shared_ptr<std::thread>> idle_list;
    std::list<std::shared_ptr<std::thread>> busy_list;
    
    void wrapper_run(std::function<void()>&& func){
        
    }
};