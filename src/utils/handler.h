//
// Created by will on 2021/8/23.
//

#ifndef CPP_STUDEY_MESSAGE_H
#define CPP_STUDEY_MESSAGE_H
#include <memory>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
class Handler;
using SptrHandler = std::shared_ptr<Handler>;
class Runnable;
using SptrRunnable = std::shared_ptr<Runnable>;
class Message;
using SptrMessage = std::shared_ptr<Message>;

class Runnable{
public:
    virtual ~Runnable();
    virtual void run()= 0;
};

class Message{
public:
    Message():_what(0),_arg1(0),_arg2(0),_when(-1){

    }
    ~Message(){
        std::cout<<"~ Message "<<std::endl;
    }

public:
    int _what;
    int _arg1;
    int _arg2;
    long _when;
    SptrMessage _next;
private:
    SptrHandler _sPtr_target;
    SptrRunnable _sPtr_callback;
};

class MessageQueue{
public:
    MessageQueue();
    ~MessageQueue(){
        std::cout<<"~MessageQueue()"<<std::endl;
    }
    bool enqueueMessage(SptrMessage sPtrMessage,long when);
    SptrMessage next();
    void quit(bool safe);

private:
    bool _quitting;
    SptrMessage _messages;
    std::mutex _modify_mutex;
    std::condition_variable _modify_condition;


};

#endif //CPP_STUDEY_MESSAGE_H
