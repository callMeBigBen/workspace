// #include "future/future_test.h"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <unordered_map>
// #include "wheels/asyncer/asyncer.h"
#include "wheels/thread_pool/thread_pool.h"
// #include <cpputil/pool/thread_pool.h>
#include <atomic>

using TaskFunc = std::function<void()>;
using namespace std::chrono;

int main()
{
    size_t task_size = 10000;
    size_t thread_num = 64;
    size_t buffer_size = 256;
    ThreadPool<TaskFunc> thread_pool(thread_num, buffer_size);
    milliseconds start_ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    // test case 1: vector assign
    
    auto vec = std::vector<int>();
    for (int i = 0; i < task_size; i++){
        vec.push_back(2000000);
    }
    unordered_map<int, atomic<int>> mp;
    mp.reserve(task_size*2);
    cout<<"vec size:"<<vec.size()<<endl;
    auto func = [&](int i)->void{
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        mp[i].fetch_add(1);
        vec[i] = i;
    };
    for (int i = 0; i < task_size; i++)
    {
        auto task = std::bind(func, i);
        while(!thread_pool.async_enqueue(task)) {} 
    }
    
    
   
    // tese case 2: long-time attack
    /*
    auto name = "shawn";
    auto func = [&]()->void{
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        printf("name:%s\n", name);
    };
    for(int i = 0;i < task_size; i++){
        while(true) {
            if(thread_pool.async_enqueue(func)){
                break;
            }
        } 
    }
    */
    

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    thread_pool.stop();
    for(auto& num : vec){
        std::cout<<num<<std::endl;
    }
    for(auto& p : mp)
        printf("%d:%d\n",p.first, p.second.load());
    milliseconds end_ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    printf("total time ms: %ld", end_ms - start_ms);
    return 1;
}