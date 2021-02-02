#include <folly/futures/Future.h>
#include <iostream>
using namespace std;

void foo(int x){
    cout<< "foo("<<x<<")"<<std::endl;
}

int future_test(){
    folly::Promise<int> p;
    folly::Future<int> f = p.getFuture();
    std::move(f).then(foo);
    p.setValue(5);
    cout<<"promise fulfilled"<<std::endl;
    return 1;
}