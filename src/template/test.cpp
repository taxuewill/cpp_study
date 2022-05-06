//
// Created by will on 2022/5/6.
//

#include "template/test.h"
using namespace std;

PositionBuilder::PositionBuilder() {
    cout << "Create PositionBuilder" << endl;
    builder_ = this;
}

PositionBuilder &PositionBuilder::SetGps(int la, int lo) {
    la_ = la;
    lo_ = lo;
    return *this;
}

void PositionBuilder::DoSomething() {
    cout << "Id:" << id_ << "\n" << "Gps is (" << la_ << "," << lo_ << ")" << endl;
}

PositionBuilder::~PositionBuilder() {
    cout << "Destroy PositionBuilder" << endl;
}


ChargePileBuilder::ChargePileBuilder() {
    cout << "Create ChargePileBuilder" << endl;
    builder_ = this;
}

ChargePileBuilder &ChargePileBuilder::SetXYTheta(int x, int y, int theta) {
    x_ = x;
    y_ = y;
    theta_ = theta;
    return *this;
}

void ChargePileBuilder::DoSomething() {
    cout << "Id:" << id_ << endl;
    cout << "position is (" << x_ << "," << y_ << "," << theta_ << ")" << endl;
}

ChargePileBuilder::~ChargePileBuilder() {
    cout << "Destroy ChargePileBuilder" << endl;
}


int main() {
    cout << "hello,builder!" << endl;
    PositionBuilder position_builder;
    position_builder.SetId(1234).SetGps(1, 2).DoSomething();
    printf("----------------\n");
    ChargePileBuilder charge_pile_builder;
    charge_pile_builder.SetId(4321).SetXYTheta(10, 20, 1).DoSomething();

    return 0;
}