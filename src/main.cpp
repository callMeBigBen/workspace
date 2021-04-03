// #include "future/future_test.h"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>
// #include "wheels/asyncer/asyncer.h"
#include "wheels/thread_pool/thread_pool.h"
// #include <cpputil/pool/thread_pool.h>

using TaskFunc = std::function<void()>;

int main()
{
    auto task_size = 100;
    auto thread_size = 10;
    ThreadPool<TaskFunc> thread_pool(thread_size, task_size);
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

    // test case 1: vector assign
    
    auto vec = std::vector<int>();
    for (int i = 0; i < task_size; i++){
        vec.push_back(10000);
    }
    auto func = [&](int i)->void{
        if(vec[i] == i){
            std::cout<<"oh my gush!"<<std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        vec[i] = i;
    };
    for (int i = 0; i < task_size; i++)
    {
        auto task = std::bind(func, i);
        while(true) {
            if(thread_pool.async_enqueue(task)){
                break;
            }
        } 
    }
    
   
    // tese case 2: long-time attack
    // failed
    /*
    auto name = "shawn";
    auto func = [&]()->void{
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::cout<<name<<std::endl;
    };
    for(int i = 0;i < 2000; i++){
        while(true) {
            if(thread_pool.async_enqueue(func)){
                break;
            }
        } 
    }
    */

    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    thread_pool.stop();
    for(auto& num : vec){
        std::cout<<num<<std::endl;
    }
    return 1;
}