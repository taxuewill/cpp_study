//
// Created by will on 2021/6/8.
//

#include <iostream>
using namespace std;

class Parent{
public:
    int age = 10;
    Parent(){
        cout<<"create Parent"<<endl;
    }
};

class Child : public Parent{
public:
    Child(){
        cout<<"create Child"<<endl;
    }

    ~Child(){
        cout<<"destruct Child"<<endl;
    }
};

int main(){
    Child * pChild = new Child();
    cout<<pChild->age<<endl;
    delete pChild;
    return 0;
}