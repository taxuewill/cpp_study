//
// Created by will on 2021/8/23.
//

#include "handler.h"

using namespace std::chrono;

MessageQueue::MessageQueue() :_quitting(false){

}

bool MessageQueue::enqueueMessage(SptrMessage sPtrMessage, long when) {
    std::lock_guard<std::mutex> lock(_modify_mutex);
    if(_quitting){
        std::cout<<"quitting !!! Can not enqueue "<<std::endl;
    }
    SptrMessage p = _messages;
    if(!p || when == 0||when < p->_when){
        sPtrMessage->_next = p;
        _messages = sPtrMessage;
    }else{
        SptrMessage prev;
        for(;;){
            prev = p;
            p = p->_next;
            if(!p||when<p->_when){
                break;
            }
        }
        sPtrMessage->_next = p;
        prev->_next = sPtrMessage;
    }
    _modify_condition.notify_all();
    return true;

}

SptrMessage MessageQueue::next() {
    for(;;){
        {
            milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            std::unique_lock<std::mutex> lock;
            SptrMessage prevMessage;
            SptrMessage messageHeader = _messages;
        }

    }
}

void MessageQueue::quit(bool safe) {

}

