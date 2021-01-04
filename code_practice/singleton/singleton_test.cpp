#include "singleton.h"
#include <thread>
#include <chrono>

SingletonManager SingletonManager::instance_;

int main(){
    std::string str = "abc";
    SingletonManager::init(str);
    while(1){
        std::cout<<SingletonManager::instance().member<<std::endl;
    }
}