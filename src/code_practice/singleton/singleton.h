#include <string>
#include <iostream>
// best practices of Singleton
class SingletonManager {
public:
    ~SingletonManager() = default;

    static SingletonManager &instance(){
        return instance_;
    }
    static void init(std::string& str){
        instance_.member = str;
    }
    std::string member;

private:
    static SingletonManager instance_;
    SingletonManager() = default;
    SingletonManager(SingletonManager &) = delete; // privatize copy constructor to keep the singleton unique
    SingletonManager &operator=(SingletonManager &) = delete;
};
