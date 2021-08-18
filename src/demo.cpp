//
// Created by will on 2021/8/18.
//

#include "utils/timer_task.h"
#include <iostream>
#include <memory>
#include <functional>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

mutex cv_m;
condition_variable cv;

void worker_thread(){
    std::unique_lock<mutex> lk(cv_m);
    if(cv.wait_for(lk,chrono::seconds(2))==std::cv_status::timeout){
        cout<<"timeout do something"<<endl;
    }else{
        cout<<"canceled"<<endl;
    }
}

class MyDelayTask : public TimerTask{
public:
    void run(){
        cout<<"this is MyDelayTask"<<endl;
    }
};

int main(int argc,char ** argv){
    std::shared_ptr<TimerTask> pTask = std::make_shared<MyDelayTask>();
    std::shared_ptr<CppTimer> pTimer = std::make_shared<CppTimer>();
    pTimer->startWithDelay(pTask,3);
    int i;
    cin >>i;
    if(i==1){
        pTimer->cancel();
    }
    return 0;
}

