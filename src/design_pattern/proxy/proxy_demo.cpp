#include "proxy_demo.h"
#include <cstdlib>
#include <iostream>

using namespace design_pattern;
using namespace std;

void RealSubject::request(){
    cout<<"RealSubject handle request."<<endl;

}

Proxy::Proxy():m_pRealSubject(new RealSubject()){
    cout<<"create Proxy"<<endl;
}

Proxy::~Proxy(){
    if(m_pRealSubject){
        delete m_pRealSubject;
        m_pRealSubject = nullptr;
    }
    cout<<"destruct Proxy"<<endl;
}

void Proxy::preRequest(){
	cout << "Proxy::preRequest" << endl;
}

void Proxy::afterRequest(){
	cout << "Proxy::afterRequest" << endl;
}

void Proxy::request(){
    preRequest();
    cout<<"Proxy"<<endl;
    m_pRealSubject->request();
    afterRequest();
}



int main(int argc,char **argv){

    Proxy proxy;
    proxy.request();

    return EXIT_SUCCESS;
}