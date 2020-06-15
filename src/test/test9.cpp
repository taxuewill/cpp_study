#include <iostream>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <stdint.h>
#include <unistd.h>
#include <chrono>
using namespace std;

// class OperatorA{
// public:
//     bool operator()(const int a,int*b){
//         *b = a;
//         return true;
//     }

// };

// int main(int argc,char ** argv){
//     if(argc>1){
//         cout<<"param is "<<argv[1]<<endl;
//     }
//     // ofstream data("./data.txt");
//     // if(data){
//     //     for(int i = 0; i < 100; i++){
//     //         data<<i<<endl;
//     //     }
//     // }
//     // data.close();
//     // char charArray[512];
//     // ifstream inData("/home/will/data/video/data/Collection/vision_cali.data");
//     // inData.read(charArray,512);
//     // inData.close();
//     // cout<<"sizeof char "<<sizeof(char)<<endl;
//     // cout<<"sizeof float "<<sizeof(float)<<endl;
    
//     // float * pFloat =(float *) charArray;
//     // for(int i = 0;i < 128;i++){
//     //     printf("[%d] is %f \n",i,*pFloat);
//     //     pFloat++;
//     // }
//     return 0;
    
// }



std::mutex mtx; // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
bool ready = false; // 全局标志位.

void do_print_id(int id)
{
    cout<<"do_print_id "<<id<<"\n"<<endl;
    std::unique_lock <std::mutex> lck(mtx);

    // while (!ready){
        cout<<"start wait"<<endl;
        cv.wait_for(lck,chrono::seconds(1)); // 当前线程被阻塞, 当全局标志位变为 true 之后,
        cout<<"end wait"<<endl;
    // } // 如果标志位不为 true, 则等待...
        
    // 线程被唤醒, 继续往下执行打印线程编号id.
    std::cout << "thread " << id << " continue "<<std::endl;
}

void go()
{
    cout<<"go ....."<<endl;
    std::unique_lock <std::mutex> lck(mtx);
    ready = true; // 设置全局标志位为 true.
    cout<<"start sleep 10s"<<endl;
    sleep(10);
    cv.notify_all(); // 唤醒所有线程.
}

int main()
{
    std::thread thread(do_print_id, 1);
    cout<<"sleep 11 \n"<<endl;
    sleep(11);
    cout<<"end sleep "<<std::endl;
    // go(); // go!
    thread.join();

    return 0;
}