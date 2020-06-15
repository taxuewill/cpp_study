#include <iostream>

using namespace std;

#include <ctime>
// Eigen 核心部分
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆，特征值等）
#include <Eigen/Dense>

using namespace Eigen;

int main(){
    cout<<"hello algo"<<endl;
    Matrix3d rotation_matrix = Matrix3d::Identity();
    cout<<"rotation_matrix is :"<<endl;
    cout<<rotation_matrix<<endl;
    cout<<"trace is "<<rotation_matrix.trace()<<endl;
    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));     //沿 Z 轴旋转 45 度
    cout<<"沿 Z 轴旋转 45 度 R is "<<endl;
    cout<<rotation_vector.matrix()<<endl;
    AngleAxisd rotation_vector_negative(-M_PI / 4, Vector3d(0, 0, 1));     //沿 Z 轴旋转 45 度
    cout<<"沿 Z 轴旋转 -45 度 R is "<<endl;
    cout<<rotation_vector_negative.matrix()<<endl;
    Eigen::Matrix3d result = rotation_vector_negative.matrix()*(rotation_vector.matrix());
    cout<<"result is \n"<<result<<endl;
    // rotation_matrix = rotation_vector.matrix();
    // Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 1); // ZYX顺序，即yaw-pitch-roll顺序
    // cout << "yaw pitch roll = " << euler_angles.transpose() << endl;
    return 0;
}