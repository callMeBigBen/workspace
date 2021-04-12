// #include "future/future_test.h"
#include <iostream>
#include <atomic>

class Base {
public:
    virtual void print(){
        std::cout<<"Base"<<std::endl;
    }
};

class Derived :public Base{
public:
    virtual void print() override{
        std::cout<<"Derived"<<std::endl;
    }
};

template<typename ClassType>
class Printer{
public:
    void do_print(){
        ClassType t;
        t.print();
    }
};

int main(){
    std::atomic<int> a(3);
    std::cout<<a.fetch_add(1)<<std::endl;
}