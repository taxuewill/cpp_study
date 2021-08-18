//
// Created by will on 2021/8/18.
//

#include "utils/cpp_timer.h"
#include <iostream>
#include <memory>
#include <functional>

using namespace std;
using namespace robot_util;

class MyObject{
public:
    MyObject(){
        cout<<"create MyObject"<<endl;
    }
    void test(int i){
        cout<<"this is test "<<i<<endl;
    }
};

int main(int argc,char ** argv){
    using namespace std::placeholders;
    cout<<"this is demo"<<endl;
    std::shared_ptr<CTimer> ptimer = std::make_shared<CTimer>("ctimer1");
    MyObject object;
//    ptimer->AsyncOnce(1000,[&](){
//       cout<<"delay 1000ms "<<endl;
//       object.test(10);
//    });
    ptimer->AsyncOnce(1000,std::bind(&MyObject::test,object,2));
    int i =0 ;
    cin >> i;

    return 0;
}

