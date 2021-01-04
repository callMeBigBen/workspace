#include <string>
#include <iostream>

template <class T>
T foo(int i){
    return static_cast<T>(i);
}

void const_cast_test(){
    // int raw = 5;
    // const int* a = &raw;
    // int* b = const_cast<int*>(a);
    // std::cout<<b<<std::endl;
    // std::cout<<a<<std::endl;
    // *b = 4;
    // std::cout<<b<<std::endl;
    // std::cout<<a<<std::endl;
    // std::cout<<*b<<std::endl;
    // std::cout<<*a<<std::endl;
    const int a = 5;
    int& b = const_cast<int&>(a);
    std::cout<<&b<<std::endl;
    std::cout<<&a<<std::endl;
    b = 4;
    std::cout<<&b<<std::endl;
    std::cout<<&a<<std::endl;
    std::cout<<b<<std::endl;
    std::cout<<a<<std::endl;
}

int main(){
    // int i = 1;
    // std::cout<<foo<std::string>(i)<<std::endl;
    const_cast_test();
}