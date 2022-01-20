//
// Created by will on 2021/8/18.
//

#include "timer_task.h"
#include <iostream>

void TimerTask::start() {
    this->run();
}

CppTimer::CppTimer():_work_thread(nullptr),_start_flag(false){

}

void CppTimer::startWithDelay(std::shared_ptr<TimerTask> task, long second) {
    std::cout<<"starWithDelay"<<std::endl;

    if(!_start_flag){
        _start_flag = true;
        if(!_work_thread){
            _work_thread = new std::thread([this,task,second](){
                std::unique_lock<std::mutex> lk(_mutex);
                if(_cv.wait_for(lk,std::chrono::seconds(second)) == std::cv_status::timeout){
                    task->start();
                }else{
                    std::cout<<"cancel task"<<std::endl;
                }
            });
        }
    }
}

void CppTimer::cancel() {

    if(_start_flag){
        _cv.notify_all();
        _start_flag = false;
    }
}

CppTimer::~CppTimer() {
    std::cout<<"~CppTimer"<<std::endl;
    _start_flag = false;
    if(!_work_thread){

        std::cout<<"clean work thread"<<std::endl;
        _cv.notify_all();
        _work_thread->join();
        delete _work_thread;
        _work_thread = nullptr;
    }
}