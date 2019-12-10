#include <cassert>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

std::atomic<int> cnt = {0};

void f(){
    for(int n = 0; n <1000;++n){
        cnt.fetch_add(1, std::memory_order_relaxed);
    }
}

int main(int argc,char** argv){

    cout<<"Hello,Atomic"<<endl;
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n) {
        v.emplace_back(f);
    }
    for (auto& t : v) {
        t.join();
    }
    assert(cnt == 10000);    // never failed
    cout<<"End"<<endl;
}