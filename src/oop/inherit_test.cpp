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
    int HASH_INCREMENT = 0x61c88647;
    int n = 6;
    if(true && false || false && true){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }
    switch (n) {
        case 1:
        case 5:{
            cout<<"this is 1 or 5"<<endl;
            break;
        }
        case 6:{
            cout<<"this is 6 "<<endl;
            break;
        }
    }
}