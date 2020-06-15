#include <iostream>

using namespace std;

#include <ctime>

#include <Eigen/Core>
#include <Eigen/Dense>
#include "sophus/se3.hpp"

using namespace Eigen;

int main(){
    cout<<"hello world"<<endl;

    Matrix3d R = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();

    cout<<"R is "<<endl;
    cout<<R<<endl;
    Sophus::SO3d SO3_R(R);
    cout << "SO(3) from matrix:\n" << SO3_R.matrix() << endl;

}