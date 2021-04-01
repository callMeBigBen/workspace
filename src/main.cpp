// #include "future/future_test.h"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>
// #include "wheels/asyncer/asyncer.h"
#include "wheels/thread_pool/thread_pool.h"
#include <cpputil/pool/thread_pool.h>

using TaskFunc = std::function<void()>;

int main()
{
    ThreadPool<TaskFunc> thread_pool(10, 100);
    // cpputil::pool::ThreadPool thread_pool(10, "", 100);
    // std::cout<<"init finished"<<std::endl;
    // std::vector<folly::Future<int>> future_vec;
    // auto lamb = [](int a, int b, int c) -> void {
    //     std::this_thread::sleep_for(std::chrono::seconds(c));
    //     std::cout << "hello " << std::to_string(a) << " " << std::to_string(b) << std::endl;
    // };
    // for (int i = 0; i < 10; i++)
    // {
    //     future_vec.push_back(std::move(asyncer(lamb, i, i + 1, i+2)));
    // }
    // for(auto& fut : future_vec){
    //     std::move(fut).get();
    //     std::cout<<"fut done"<<std::endl;
    // }
    auto vec = std::vector<int>();
    for (int i = 0; i < 100; i++){
        vec.push_back(10000);
    }
    auto func = [](int i, auto& vec)->void{
        std::ostringstream out;  
        out<<"in func, i:"<<i<<std::endl;
        std::cout<<out.str();
        vec[i] = i;
    };
    for (int i = 0; i < 100; i++)
    {
        // auto&& task = std::bind(func, i, vec);
        // thread_pool.async_enqueue(std::move(task));
        auto task = std::bind(func, i, std::ref(vec));
        while(true) {
            if(thread_pool.async_enqueue(task)){
                break;
            }
        } 
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    thread_pool.stop();
    for(auto& i : vec){
        std::cout<<i<<std::endl;
    }
    return 1;
}