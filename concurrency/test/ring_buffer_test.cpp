#include "concurrency/lock_free/ring_buffer.h"
#include <iostream>
#include <thread>

class Item {
public:
    ~Item() = default;
    Item(std::string&& item_id, std::string&& item_content){
        item_id_ = std::move(item_id);
        item_content_ = std::move(item_content);
    }
    Item(Item&& item){
        item_id_ = std::move(item.item_id_);
        item_content_ = std::move(item.item_content_);
    }
    std::string item_id_;
    std::string item_content_;
};

void correctness_test(int producer_num, int comsumer_num){
    /**
     * args specification:
     */
    
}

int main(){
    correctness_test(5,5);
}