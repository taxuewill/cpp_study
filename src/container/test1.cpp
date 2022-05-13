//
// Created by will on 2022/5/12.
//
#include <iostream>
#include <list>

using namespace std;

void traverse(const list<int> & container){
    for(auto e : container){
        cout<<e<<" ";
    }
    cout<<endl;
}

int main(int argc,char ** argv){

    cout<<"Hello,container"<<endl;
    std::list<int> a1 {1,2,3},a2{4,5,6};
    cout<<"a1 is:"<<endl;
    traverse(a1);
    cout<<"a2 is:"<<endl;
    traverse(a2);

    a1.swap(a2);

    cout<<"now a1 is:"<<endl;
    traverse(a1);
    cout<<"now a2 is:"<<endl;
    traverse(a2);



    return 0;
}