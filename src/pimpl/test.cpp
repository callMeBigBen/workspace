#include <memory>
#include <iostream>

struct B{
    std::string s;
};

struct A{
std::string s;
int i;
B b;
};

int main(){
    auto p1 = std::make_shared<A>();
    p1->s = "123";
    p1->i = 2;
    p1->b.s = "123";
    auto p2 = std::make_shared<A>(*p1);
    p2->s = "345";
    p2->b.s = "345";
    std::cout<<p1->b.s<<std::endl;
    std::cout<<p2->b.s<<std::endl;
}