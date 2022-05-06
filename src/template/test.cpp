//
// Created by will on 2022/5/6.
//
#include <iostream>
#include <memory>



using namespace std;

template<typename T>
class BaseBuilder{

public:
    BaseBuilder(){
        cout<<"create BaseBuilder"<<endl;
//        builder_ = make_shared<T>();
    }

    T & SetId(int id){
        id_ = id;
        return *builder_;
    }

    virtual void DoSomething() = 0;

    ~BaseBuilder(){
        cout<<"Destroy BaseBuilder"<<endl;
    }
protected:
    int id_;
    T * builder_;
};

class PositionBuilder : public BaseBuilder<PositionBuilder>{
public:
    PositionBuilder(){
        cout<<"Create PositionBuilder"<<endl;
        builder_ = this;
    }

    PositionBuilder & SetGps(int la,int lo){
        la_= la;
        lo_ = lo;
        return *this;
    }

    void DoSomething(){
        cout<<"Id:"<<id_<<"\n"<<"Gps is ("<<la_<<","<<lo_<<")"<<endl;
    }

    ~PositionBuilder(){
        cout<<"Destroy PositionBuilder"<<endl;
    }

private:
    int la_;
    int lo_;

};

class ChargePileBuilder : public BaseBuilder<ChargePileBuilder>{
public:
    ChargePileBuilder(){
        cout<<"Create ChargePileBuilder"<<endl;
        builder_ = this;
    }

    ChargePileBuilder & SetXYTheta(int x,int y,int theta){
        x_ = x;
        y_ = y;
        theta_ = theta;
        return *this;
    }

    void DoSomething(){
        cout<<"Id:"<<id_<<endl;
        cout<<"position is ("<<x_<<","<<y_<<","<<theta_<<")"<<endl;
    }

    ~ChargePileBuilder(){
        cout<<"Destroy ChargePileBuilder"<<endl;
    }
private:
    int x_;
    int y_;
    int theta_;

};

int main(){
    cout<<"hello,builder!"<<endl;
    PositionBuilder position_builder;
    position_builder.SetId(1234).SetGps(1,2).DoSomething();
    printf("----------------\n");
    ChargePileBuilder charge_pile_builder;
    charge_pile_builder.SetId(4321).SetXYTheta(10,20,1).DoSomething();

    return 0;
}