#include <folly/futures/Future.h>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void foo(int x){
    cout<< "foo("<<x<<")"<<std::endl;
}
folly::Future<int> async_sleep(){
    auto p = std::make_shared<folly::Promise<int>>();
    std::thread([=]{
        p->setWith([]{
            std::this_thread::sleep_for(3s);
            return 10;
        });
    }).detach();
    return p->getFuture();
}

int future_test(){
    folly::Future<int> f = async_sleep();
    auto f2 = std::move(f).then(foo);
    std::move(f2).then([]{
        std::cout<<"in bar"<<std::endl;
    });
    cout<<"promise fulfilled"<<std::endl;
    return 1;
}