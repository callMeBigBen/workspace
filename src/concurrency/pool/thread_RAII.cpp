#include <thread>
#include <chrono>
#include <iostream>

// template<typename >
class ThreadRAII{
public:
    ThreadRAII(std::thread&& thread):t(std::move(thread)){};
    ~ThreadRAII(){
        t.join();
    }
    std::thread& get(){return t;};

private:
    std::thread t;
};

void busy_loop(){
    for(int i = 0;i < 20;++i){
        std::cout<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void foo(){
    std::thread t(busy_loop);
    ThreadRAII t_raii(std::move(t));
    std::cout<<"at exit"<<std::endl;
}
// int main(){
//     foo();
//     std::cout<<"final"<<std::endl;

// }