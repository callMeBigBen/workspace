#include <vector>
#include <atomic>

/**
 *  little demo of lock_free ring_buffer
 **/
#define DEFAULT_MAX_CAPACITY = 10000
#define MAX_VALID_CAPACITY = 4294967295  // 2^32 -1

template<class T>
class RingBuffer {
public:
    RingBuffer(){
        entries.reserve(DEFAULT_MAX_CAPACITY);
        capacity = DEFAULT_MAX_CAPACITY;
        p_index = 0;
        c_index = 0;
        p_mut.store(false);
        c_mut.store(false);
    }

    RingBuffer(int max_capacity){
        max_capacity = max_capacity <= MAX_VALID_CAPACITY ? max_capacity : MAX_VALID_CAPACITY;
        entries.reserve(max_capacity);
        capacity = max_capacity;
        p_index = 0;
        c_index = 0;
        p_mut.store(false);
        c_mut.store(false);
    }

    bool push_back(T&& t){
        if()
        while(!p_mut.compare_exchange_weak(false, true)) continue; // busy loop
        // critical section. Keep it small and simple
        entries[p_index++] = std::move(t);
        while(!p_mut.compare_exchange_weak(true, false)) continue;
        return true;
    }

    T& pop(){
        while(!c_mut.compare_exchange_weak(false, true)) continue; // busy loop
        // critical section. Keep it small and simple
        T& ret = entries[c_index--];
        while(!c_mut.compare_exchange_weak(true, false)) continue;
    }

private:
    std::vector<T> entries;
    std::atomic_uint32_t p_index;    // producer index
    std::atomic_uint32_t c_index;    // consumer index
    std::atomic_bool p_mut;
    std::atomic_bool c_mut;
    uint32_t capacity;

    bool can_produce(){
        bool ret = p_index < c_index + capacity;
        unify_offset();
        return ret;
    }

    bool can_consume(){
        bool ret = p_index > c_index;
        unify_offset();
        return ret;
    }

    void unify_offset(){
        
    }
};
