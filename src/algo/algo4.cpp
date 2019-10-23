#include <iostream>
#include <queue>
#include <list>

using namespace std;
/*C4(15min)
有一个未排序整数数组，长度已知为N，从数组找出连续长度最长的序列，多个长度相同时，取其中一组即可。
如给定数组int array[]={6,1,2,20,11,7,8,3,9}，输出为{6,7,8,9}*/

// void find(int array[]){
//     cout<<array.length<<end;
// }


void dumpQueue(queue<int> tempQueue){
    cout<<"start dump ";
    while(!tempQueue.empty()){
        cout<<tempQueue.front()<<",";
        tempQueue.pop();
    }
    cout<<"end dump"<<endl;
}


int main(int,char **){
    int array[]= {6,1,2,5,20,11,7,8,3,9};
    cout<<sizeof(array)/sizeof(int)<<endl;
    cout<<end(array)-begin(array)<<endl;

    int arraySize = end(array)-begin(array);
    list<queue<int>> tempList;
    for(int i = 0;i< arraySize;i++){
        int j = i;
        list<queue<int>> tempList;
        queue<int> tempQueue;
        tempQueue.push(array[j]);
        cout<<"tempQueue back "<<tempQueue.back()<<endl;
        for(j++;j<arraySize;j++){

            if(array[j]>=tempQueue.back()){
                tempQueue.push(array[j]);
            }
        }
        dumpQueue(tempQueue);
        tempList.push_back(tempQueue);
    }
    auto begin = tempList.begin();
    int maxSize = 0;
    auto maxIterator = tempList.begin();
    while(begin != tempList.end()){
        if(maxSize < begin->size()){
            maxSize = begin->size();
            maxIterator = begin;
        }
        cout<<"size is "<<begin->size()<<endl;
        ++begin;
    }
    
    queue<int> result = *maxIterator;
    while(!result.empty()){
        cout<<result.front()<<",";
        result.pop();
    }

    return 0;
}