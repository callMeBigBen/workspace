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

template <typename T>
void ChangeVal(T v){
    std::cout<<"before: v"<<v<<std::endl;
    v ++;
    std::cout<<"after: v"<<v<<std::endl;
}

int main(){
    int a = 5;
    int& b = a;
    int* c = &a;
    // ChangeVal(b);
    ChangeVal(c);
    std::cout<<a<<std::endl;
}