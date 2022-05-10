//
// Created by will on 2022/5/10.
//
#include <iostream>

#include <boost/function.hpp>

using namespace std;

int main(){
    cout<<"Hello,Boost!!!"<<endl;
    boost::function0<void> callback;
    if(callback){
        cout<<"callback is not null"<<endl;
    }else{
        cout<<"callback is null"<<endl;
        cout<<"empty is "<<callback.empty()<<endl;
    }

    return 0;
}

