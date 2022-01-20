//
// Created by will on 2021/8/18.
//

#ifndef CPP_STUDEY_TIMER_TASK_H
#define CPP_STUDEY_TIMER_TASK_H
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

class TimerTask{
public:
    TimerTask() = default;
    virtual ~TimerTask() = default;
    void start();
    virtual void run(){};
};

class CppTimer{
public:
    CppTimer();
    ~CppTimer();
    void startWithDelay(std::shared_ptr<TimerTask> task,long second);
    void cancel();

private:
    std::thread * _work_thread;
    std::atomic_bool _start_flag;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::shared_ptr<TimerTask> _ptr_time_task;
};

#endif //CPP_STUDEY_TIMER_TASK_H
