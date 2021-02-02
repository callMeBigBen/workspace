#include <thread>
#include <iostream>
#include <unistd.h>
#include <atomic>


std::atomic_int a,b;

void foo(void){
    b.store(1,std::memory_order_relaxed);
    a.store(1,std::memory_order_relaxed);
    // a.store(1);
    // b.store(1);
}

void bar(void){
    while(b.load(std::memory_order_relaxed)==0)continue;
    assert(a.load(std::memory_order_relaxed)==1);
    // while(b.load()==0)continue;
    // assert(a.load()==1);
}

// int main(){
//     while(true){
//         std::thread t1(bar);
//         std::thread t2(foo);
//         t1.join();
//         t2.join();
//         std::cout<<"test done"<<std::endl;
//     }
// }