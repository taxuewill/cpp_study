#include <iostream>
#include <thread>
#include <mutex>

#define LOOP_COUNT 100000

using namespace std;

int g_count =0;
mutex g_count_mutex;



void add(){

    for(int i =0;i<LOOP_COUNT;i++){
        std::unique_lock<mutex> add_lock(g_count_mutex);
        ++g_count;
        if(i%100==0){
            cout<<"add ";
        }
    }
    
}

void minuse(){
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        std::unique_lock<mutex> minuse_lock(g_count_mutex);
        --g_count;
        if(i%100==0){
            cout<<"minuse ";
        }
    }
}


int main(int argc,char **argv){
    cout<<"Hello,Thread"<<endl;
    thread threadAdd = thread(add);
    thread threadMinuse = thread(minuse);

    threadAdd.join();
    threadMinuse.join();
    cout<<"g_count is "<<g_count<<endl;
    return 0;
}