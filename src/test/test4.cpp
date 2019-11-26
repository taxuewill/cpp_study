#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
using namespace std;

std::atomic_flag flag = ATOMIC_FLAG_INIT;


void test(){
    while(flag.test_and_set()){
        cout<<"current is true"<<endl;
        sleep(1);
    }
}

int main(int argc,char ** argv){
    cout<<"Hello,C++"<<endl;
    if(flag.test_and_set()){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }
    thread t = thread(test);
    
    if(flag.test_and_set()){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    int i;
    cin>>i;
    flag.clear();
    t.join();
    cout<<"exit"<<endl;
    return 0;
}