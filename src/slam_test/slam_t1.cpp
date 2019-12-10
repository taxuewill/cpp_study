#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;

int main(int argc,char** argv){
    Matrix<int,2,3> matrix_23;
    Vector3i v_3i;
    matrix_23<<1,2,3,4,5,6;
    v_3i<<3,2,1;
    cout<<matrix_23<<endl;
    Matrix<int,2,1> result = matrix_23 * v_3i;
    cout<<"result is \n"<<result<<endl;

    return 0;
}