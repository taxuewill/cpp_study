#include <sys/eventfd.h>
#include <unistd.h>
#include <iostream>

#define LOGD(info) cout<<info<<endl

using namespace std;
int main(){
    int efd = eventfd(0,EFD_NONBLOCK|EFD_SEMAPHORE|EFD_CLOEXEC);
    if(efd<0){
        cout<<"create eventfd failed "<<endl;
    }else{
        LOGD("create fd success");
    }
    eventfd_t count;
    eventfd_write(efd,10);
    int readResult = -1;
    for (int i = 0; i < 10; i++)
    {
        readResult = eventfd_read(efd, &count);
        cout << "readResult " << readResult << ",count is " << count << endl;
    }
    readResult = eventfd_read(efd,&count);
    cout<<"readResult "<<readResult<<",count is "<<count<<endl;


    return 0;
}