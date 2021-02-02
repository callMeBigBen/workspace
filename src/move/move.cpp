#include <string>
#include <vector>
#include <iostream>

class SomethingMovable {
public:
    SomethingMovable() = default;
    SomethingMovable(SomethingMovable&& sm) = default;
    SomethingMovable& operator=(SomethingMovable&& sm) = default;


    std::string s;
    std::vector<int> v;
};

// int main(){
//     SomethingMovable sm1;
//     sm1.s = "abc";
//     sm1.v.push_back(1);
//     auto sm2 = std::move(sm1);
//     std::cout<<sm2.s<<std::endl;
//     std::cout<<sm1.s<<std::endl;
// }