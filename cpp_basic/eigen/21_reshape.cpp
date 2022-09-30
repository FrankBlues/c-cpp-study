#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace std;
int main()
{
    Eigen::Matrix4i m = Eigen::Matrix4i::Random();
    cout << "Here is the matrix m:" << endl << m << endl;
    cout << "Here is m.reshaped(2, 8):" << endl << m.reshaped(2, 8) << endl;

    cout << "Here is m.reshaped().transpose():" << endl << m.reshaped().transpose() << endl;
    cout << "Here is m.reshaped<RowMajor>().transpose():  " << endl << m.reshaped<Eigen::RowMajor>().transpose() << endl;

    // inplace
    m.resize(2,8);
    cout << "Here is the matrix m after m.resize(2,8):" << endl << m << endl;
}
