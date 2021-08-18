#include <iostream>
#include <thread>
#include <mutex>
#include <bitset>
#include <string>

using std::bitset;

std::once_flag flag1,flag2;

void simple_do_once(){
    std::call_once(flag1,[](){
        std::cout<<"Simple example: called once\n";
    });
}

void may_throw_function(bool do_throw){
    if(do_throw){
        std::cout<<"throw: call_once will retry\n";
        throw std::exception();
    }
    std::cout<<"Didn't throw, call once will not attempt again\n";
}

void do_once(bool do_throw){
    try{
        std::call_once(flag2,may_throw_function,do_throw);
    }catch (...){
        std::cout<<"got exception\n";
    }
}

int main()
{
    std::string str("1100");
    bitset<4> bs(str);
    std::cout<<"bs[0] "<<bs[0]<<std::endl;

}