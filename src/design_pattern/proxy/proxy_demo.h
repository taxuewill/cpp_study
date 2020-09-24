#ifndef PROXY_DEMO_H
#define PROXY_DEMO_H

namespace design_pattern{

class Subject{

public:
    virtual void request() = 0;

};

class RealSubject:public Subject{

public:
    void request();

};

class Proxy : public Subject{

public:
    Proxy();
    ~Proxy();
    void request();

private:
    void afterRequest();
    void preRequest();
    RealSubject * m_pRealSubject;

};


}

#endif