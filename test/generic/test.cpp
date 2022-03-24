//
// Created by will on 2022/1/20.
//

#include <atomic>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <thread>
#include <map>
#include <exception>

#include <signal.h>



using namespace std;

std::atomic<int>  ai;

int  tst_val= 4;
int  new_val= 5;
bool exchanged= false;
template<typename T , int VAL>
T addValue(T const& x){
    return x + VAL;
}


int main(int argc, char **argv) {

    vector<int> source;
    vector<int> dest;
    cout<<"size is "<<dest.size()<<endl;
    dest.resize(3);
    cout<<"size 2 is "<<dest.size()<<endl;
    source.push_back(1);
    source.push_back(2);
    source.push_back(3);
    std::transform(source.begin(),source.end(),dest.begin(), addValue<int,5>);
    for(auto temp:dest){
        cout<<temp<<" ";
    }

    return 0;
}
