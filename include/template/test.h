//
// Created by will on 2022/5/6.
//

#ifndef CPP_STUDEY_TEST_H
#define CPP_STUDEY_TEST_H

#include <iostream>

template<typename T>
class BaseBuilder {

public:
    BaseBuilder() {
        std::cout << "create BaseBuilder" << std::endl;
    }

    T &SetId(int id) {
        id_ = id;
        return *builder_;
    }

    virtual void DoSomething() = 0;

    ~BaseBuilder() {
        std::cout << "Destroy BaseBuilder" << std::endl;
    }

protected:
    int id_;
    T *builder_;
};


class PositionBuilder : public BaseBuilder<PositionBuilder> {
public:
    PositionBuilder();

    PositionBuilder &SetGps(int la, int lo);

    void DoSomething();

    ~PositionBuilder();

private:
    int la_;
    int lo_;
};


class ChargePileBuilder : public BaseBuilder<ChargePileBuilder> {
public:
    ChargePileBuilder();

    ChargePileBuilder &SetXYTheta(int x, int y, int theta);

    void DoSomething();

    ~ChargePileBuilder();

private:
    int x_;
    int y_;
    int theta_;

};

#endif //CPP_STUDEY_TEST_H
