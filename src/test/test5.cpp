#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <unistd.h>

using namespace std;

std::mutex m;
std::condition_variable cv;
bool flag = false;

void test(){
    flag = false;
    //
    cout<<"start lock"<<endl;
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk,[](){ return flag;});
    cout<<"lala"<<endl;
    lk.unlock();


}

int main(int argc,char ** argv){
    cout<<"Hello,C++"<<endl;
    int i ;
    std::thread thread1 = std::thread(test);
    cout<<"start thread1"<<endl;
    sleep(1);
    {
        cin>>i;
        std::lock_guard<std::mutex> lk(m);
        flag = true;
        cv.notify_all();
    }
    thread1.join();
    cout<<"exit"<<endl;
}