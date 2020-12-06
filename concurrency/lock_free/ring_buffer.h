#include <vector>
#include <atomic>

/**
 *  simple demo of lock_free ring_buffer
 **/
#define DEFAULT_MAX_CAPACITY = 10000
#define MAX_VALID_CAPACITY = 4294967295  // 2^32 -1

template<class T>
class RingBuffer {
public:
    RingBuffer(){
        entries.reserve(DEFAULT_MAX_CAPACITY);
        capacity_ = DEFAULT_MAX_CAPACITY;
        p_index.store(0);
        c_index.store(0);
        p_mut.store(false);
        c_mut.store(false);
    }

    RingBuffer(int max_capacity){
        max_capacity = max_capacity <= MAX_VALID_CAPACITY ? max_capacity : MAX_VALID_CAPACITY;
        entries.reserve(max_capacity);
        capacity_ = max_capacity;
        p_index.store(0);
        c_index.store(0);
        p_mut.store(false);
        c_mut.store(false);
    }

    bool push(T&& t){
        if(!can_produce()) return false;
        while(!p_mut.compare_exchange_weak(false, true)) continue; // busy loop
        // critical section. Keep it small and simple
        entries[p_index] = std::move(t);
        p_index.fetch_add(1);
        if(p_index.store() == capacity_){
            p_index.store(0)
        }
        while(!p_mut.compare_exchange_weak(true, false)) continue;
        return true;
    }

    bool pop(T& ret){
        // 多消费者
        if(!can_consume()) return false;
        while(!c_mut.compare_exchange_weak(false,true)) continue;
        // critical section. Keep it small and simple
        ret = entries[c_index.load()];
        c_index.fetch_add(1);
        if(c_index.store() == capacity_){
            c_index.store(0);
        }
        while(!c_mut.compare_exchange_weak(true,false)) continue;
        return ret;
    }

private:
    std::vector<T> entries;
    std::atomic_uint32_t p_index;    // producer index
    std::atomic_uint32_t c_index;    // consumer index
    std::atomic_bool p_mut;
    std::atomic_bool c_mut;
    uint32_t capacity_;

    bool can_produce(){
        bool ret = p_index.load() < c_index.load() + capacity_;
        return ret;
    }

    bool can_consume(){
        bool ret = p_index.load() > c_index.load();
        return ret;
    }
};
