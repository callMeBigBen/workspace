// #include "future/future_test.h"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>
// #include "wheels/asyncer/asyncer.h"
#include "wheels/thread_pool/thread_pool.h"

using TaskFunc = std::function<void()>;

int main()
{
    ThreadPool<TaskFunc> thread_pool(100, 10000);
    std::cout<<"init finished"<<std::endl;
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
    for (int i = 0; i < 1000; i++)
    {
        auto&& func = [](int i)->void{
            // std::cout<<"hello, "<<i<<std::endl;
        };
        thread_pool.async_enqueue(std::move(std::bind(func, i)));
    }
    return 1;
}