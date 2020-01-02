#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;

int main(int argc, char **argv)
{
    
    Matrix2d matrix_22 ;
    matrix_22(0,0) = -2;
    matrix_22(0,1) = 1;
    matrix_22(1,0) = 4;
    matrix_22(1,1) = -3;
    
    cout<<matrix_22<<endl;
    Matrix2d inverse = matrix_22.inverse();
    cout<<inverse<<endl;

    Matrix2d e = matrix_22 * inverse;
    cout<<e<<endl;



    return 0;
}