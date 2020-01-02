#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

int main(int argc, char **argv)
{
    cout << "Hello Geometry" << endl;
    Matrix3d rotation_matrix = Matrix3d::Identity();
    cout << rotation_matrix << endl;
    // 旋转向量使用 AngleAxis, 它底层不直接是Matrix，但运算可以当作矩阵（因为重载了运算符）
    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1)); //沿 Z 轴旋转 45 度
    cout.precision(3);
    cout << "rotation matrix =\n"
         << rotation_vector.matrix() << endl; //用matrix()转换成矩阵
    rotation_matrix = rotation_vector.toRotationMatrix();
    cout << rotation_matrix << endl;
    Vector3d v(1, 0, 0);
    Vector3d v_rotated = rotation_vector * v;
    v_rotated = rotation_matrix * v;
    cout << "(1,0,0) after rotation (by angle axis) = \n"
         << v_rotated << endl;

    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZYX顺序，即roll pitch yaw顺序
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

    // 欧氏变换矩阵使用 Eigen::Isometry
    Isometry3d T = Isometry3d::Identity(); // 虽然称为3d，实质上是4＊4的矩阵
    T.rotate(rotation_vector);             // 按照rotation_vector进行旋转
    T.pretranslate(Vector3d(1, 3, 4));     // 把平移向量设成(1,3,4)
    cout << "Transform matrix = \n"
         << T.matrix() << endl;

    // 用变换矩阵进行坐标变换
    Vector3d v_transformed = T * v; // 相当于R*v+t
    cout << "v tranformed = \n"
         << v_transformed << endl;
    Quaterniond q = Quaterniond(rotation_vector);
    cout << "quaternion from rotation vector = " << q.coeffs().transpose()
       << endl;   // 请注意coeffs的顺序是(x,y,z,w),w为实部，前三者为虚部
     // 也可以把旋转矩阵赋给它
    q = Quaterniond(rotation_matrix);
    cout << "quaternion from rotation matrix = " << q.coeffs().transpose() << endl;   
    // 使用四元数旋转一个向量，使用重载的乘法即可
  v_rotated = q * v; // 注意数学上是qvq^{-1}
  cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
  cout << "should be equal to " << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << endl;

}