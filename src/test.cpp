#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <time.h>
#include <thread>
using namespace std;

class KVStore {
public:
    const int LEN = 10;
    size_t start_time_s;
    size_t delta = 0;
    unordered_map<string, string> mp;
    vector<pair<size_t, size_t> > puts;
    vector<pair<size_t, size_t> > gets;
        

    KVStore(){
        puts = vector<pair<size_t, size_t> >(LEN, {0,0});
        gets = vector<pair<size_t, size_t> >(LEN, {0,0});
        start_time_s = time(NULL);
    }
    
    void put(string k, string v){
        size_t cur_sec = time(NULL);
        size_t idx = (cur_sec - start_time_s) % LEN;
        if(cur_sec == puts[idx].second){
            puts[idx].first ++;
        }else{
            if(puts[idx].first == 0){
                puts[idx] = {puts[(idx-1)%LEN].first + 1, cur_sec};
            }else{
                size_t tmp = puts[idx].first;
                puts[idx] = {puts[(idx-1)%LEN].first -  puts[idx].first - delta + 1, cur_sec};
                delta = tmp;
            }         
        }
        mp[k] = v;
    }
    
    size_t getPutQPS(){
        size_t cur_sec = time(NULL);
        size_t idx = (cur_sec - start_time_s) % LEN;
        return puts[idx].first / LEN;
    }
};


int main()
{
    KVStore kv;
    for(int i = 0; i < 50000; ++i){
        kv.put("a", "B");
        this_thread::sleep_for(20ms);
        cout<<i + " QPS:"<<kv.getPutQPS()<<endl;
        for(auto& p : kv.puts){
            cout<<p.first<<" ";
        }
        cout<<endl;
    }
    return 0;
}