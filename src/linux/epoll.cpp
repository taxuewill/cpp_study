#include <sys/eventfd.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <iostream>
#include <thread>
#include <cstring>
using namespace std;
#define LOGD(info) cout<<info<<endl

int epollFd;
int eventFd;

bool execFlag = true;

bool init(){
    epollFd = epoll_create(10);
    if(epollFd<0){
        LOGD("create epollFd failed");
        return false;
    }
    eventFd = eventfd(0,EFD_CLOEXEC|EFD_NONBLOCK);
    if(eventFd < 0){
        LOGD("create eventfd failed");
        return false;
    }
    struct epoll_event eventItem;
    memset(&eventItem,0,sizeof(epoll_event));
    eventItem.events = EPOLLIN;
    eventItem.data.fd = eventFd;
    int result = epoll_ctl(epollFd,EPOLL_CTL_ADD,eventFd,&eventItem);
    if(result != 0){
        LOGD("epoll_ctl add failed");
        return false;
    }
    return true;
}

void readLoop(){
    LOGD("enter readLoop...");
    while(execFlag){
        struct epoll_event eventItems[10];
        LOGD("epoll_wait");
        int eventCount = epoll_wait(epollFd, eventItems, 10, -1);
        cout<<"eventCount "<<eventCount<<endl;
        if(eventCount>0){
            for(int i = 0;i<eventCount;i++){
                int fd = eventItems[i].data.fd;
                uint32_t epollEvents = eventItems[i].events;
                if(fd == eventFd){
                    LOGD("eventFd has event");
                    if(epollEvents&EPOLLIN){
                        eventfd_t count;
                        int readResult = eventfd_read(eventFd,&count);
                        if(readResult<0){
                            LOGD("read failed");
                        }else{
                            cout<<"Read count is "<<count<<endl;
                        }
                    }
                }
            }
        }
    }
    LOGD("leave readLoop...");
}


int main(){
    LOGD("Epoll test");
    if(init()){
        LOGD("init success");
    }
    int i;
    LOGD("input number");
    std::thread readThread = std::thread(readLoop);
    do{ 
        cin>>i;
        if(i<0){
            eventfd_write(eventFd,1);
        }else{
            eventfd_write(eventFd,i);
        }    
    }while(i >0);
    execFlag = false;
    cout<<"leave main"<<endl;
    eventfd_write(eventFd,1);
    readThread.join();
    if(eventFd>0){
        close(eventFd);
    }
    if(epollFd>0){
        close(epollFd);
    }
    return 0;
}