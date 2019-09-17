#include <iostream>

#include "moodycamel/readerwriterqueue.h"

using namespace moodycamel;

using namespace std;

int main(int argc,char** argv){
    cout<<"Hello,cpp"<<endl;
    ReaderWriterQueue<int> q(100);
    q.enqueue(17);
    int number;
    bool flag = q.try_dequeue(number);
    cout<<"flag "<<flag<<",number is "<<number<<endl;

    return 0;
}