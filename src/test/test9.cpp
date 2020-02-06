#include <iostream>
#include <unistd.h>
#include <string>
#include <chrono>
using namespace std;

int main(int argc,char ** argv){
    if(argc>1){
        cout<<"param is "<<argv[1]<<endl;
    }
    cout<<"start"<<endl;
    auto start = chrono::steady_clock::now();
    sleep(1);
    auto end = chrono::steady_clock::now();
    cout<<"cost time "<<(chrono::duration_cast<chrono::microseconds>(end - start)).count()<<endl;
    cout<<"end..."<<endl;
}