#pragma once
#include <iostream>
#include <folly/futures/Future.h>
#include "wheels/thread_pool/thread_pool.h"

decltype(auto) print(){
    std::cout<<std::endl;
}

template <typename... Args>
decltype(auto) print(auto&& a, Args&&... rest){
    std::cout<<a<<" ";
    print(std::forward<Args&&>(rest)...);
}

template <typename... Args>
decltype(auto) start_print(Args&&... rest){
    print(std::forward<Args&&>(rest)...);
}

template <typename Runnable, typename... Args>
decltype(auto) asyncer(Runnable&& r, Args&&... args){
    const auto& thread_pool = ThreadPoolManager::get();
    auto promise = std::make_shared<folly::Promise<int>>();
    auto future = promise->getFuture();
    start_print(std::forward<Args&&>(args)...);
    std::function<void(Args&&... args)>&& func = [&, promise](Args&&... args)->void{
        r(std::forward<Args>(args)...);
        promise->setValue(1);
    };
    std::function<void()>&& task = std::bind(func, std::forward<Args&&>(args)...);
    thread_pool.async_enqueue(std::move(task));
    return future;
}