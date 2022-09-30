#include <iostream>
#include <eigen3/Eigen/Dense>
 
int main()
{
    Eigen::MatrixXcf a = Eigen::MatrixXcf::Random(2,2);
    std::cout << "Here is the matrix a\n" << a << std::endl;
    std::cout << "Here is the matrix a^T\n" << a.transpose() << std::endl;
    std::cout << "Here is the conjugate of a\n" << a.conjugate() << std::endl;
    std::cout << "Here is the matrix a^*\n" << a.adjoint() << std::endl;

    a.transposeInPlace();
    std::cout << "and after being transposed:\n" << a << std::endl;
}