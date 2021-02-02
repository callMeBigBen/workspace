#include <memory>
#include <iostream>


struct Obj {
    int a;
};

// int main(){
//     auto obj_ptr = std::make_unique<Obj>();
//     obj_ptr->a = 10;
//     auto obj_ptr2 = std::move(obj_ptr);
//     std::cout<<obj_ptr2->a<<std::endl;
//     std::cout<<std::to_string(obj_ptr==nullptr)<<std::endl;
//     // std::cout<<obj_ptr->a<<std::endl;
// }