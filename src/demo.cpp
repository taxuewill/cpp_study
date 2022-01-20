//
// Created by will on 2021/8/18.
//

#include <iostream>
#include <future>
#include <tuple>
#include <thread>


using namespace std;

const string kOne("one");

template<typename T>
inline T max(const T & l,const T& r){
    return l>r?l:r;
}

template<class T>
T get(){
    return{};
}

struct User{
    string name;
    int age;
};

int asyncWork(){
    return 10;
}

std::string time() {
    static auto start = std::chrono::steady_clock::now();
    std::chrono::duration<double> d = std::chrono::steady_clock::now() - start;
    return "[" + std::to_string(d.count()) + "s]";
}

void OutOfMem(int value){
    std::cerr<<"Unable to satisfy request for memory\n";
    std::abort();
}

struct Foo {
    int value;
    void f() { std::cout << "f(" << this->value << ")\n"; }
    void g() { std::cout << "g(" << this->value << ")\n"; }
};

void apply(Foo* foo1,Foo* foo2,void (Foo::*func)()){
    (foo1->*func)();
    (foo2->*func)();
}

int main(int argc, char **argv) {
    const int a = 1;
    const int b = 2;
    const int * p = &a;
    p = & b;
    cout<< * p<<endl;

    int c = 5;
    int d = 10;
    int * const f = &c;
    static int s_a;
    cout<<s_a<<endl;
    return 0;
}

