//
// Created by will on 2022/3/29.
//
#include <future>
#include <iostream>

using namespace std;

template<typename F,typename... Ts>
inline
std::future<typename std::result_of<F(Ts...)>::type>
reallyAsync(F&& f,Ts&&... params){
    return std::async(std::launch::async,
                      std::forward<F>(f),
                      std::forward<Ts>(params)...);
}

template <typename T>
void Test1(const T & param){
    cout<<"this is const T &"<<endl;
}

template <typename T>
void Test1(T * param){
    cout<<"this is T *"<<endl;
}


int main(int argc,char ** argv){
    cout<<""<<endl;
    const string test("hello");
    Test1(test);
    Test1(&test);
}