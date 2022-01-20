//
// Created by will on 2021/8/19.
//

#include "foo.h"
#include "iostream"
template<typename T>
void foo(){
    std::cout<<"Here I am!\n";
}

template void foo<int>();

inline void Dramatic::info() {
    std::cout<<"It is dramatic"<<std::endl;
}