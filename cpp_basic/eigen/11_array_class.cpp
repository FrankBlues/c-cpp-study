#include <iostream>
#include <eigen3/Eigen/Dense>

int main()
{
    Eigen::ArrayXXf  m(2,2);
    
    // assign some values coefficient by coefficient
    m(0,0) = 1.0; m(0,1) = 2.0;
    m(1,0) = 3.0; m(1,1) = m(0,1) + m(1,0);
    
    // print values to standard output
    std::cout << m << std::endl << std::endl;
    
    // using the comma-initializer is also allowed
    m << 1.0,2.0,
        3.0,4.0;
        
    // print values to standard output
    std::cout << m << std::endl;


    /// add and sub
    Eigen::ArrayXXf a(3,3);
    Eigen::ArrayXXf b(3,3);
    a << 1,2,3,
        4,5,6,
        7,8,9;
    b << 1,2,3,
        1,2,3,
        1,2,3;
        
    // Adding two arrays
    std::cout << "a + b = " << std::endl << a + b << std::endl << std::endl;
    
    // Subtracting a scalar from an array
    std::cout << "a - 2 = " << std::endl << a - 2 << std::endl;

    /// multi
    std::cout << "a * b = " << std::endl << a * b << std::endl;

    Eigen::ArrayXf a1 = Eigen::ArrayXf::Random(5);
    a1 *= 2;
    std::cout << "a1 =" << std::endl
                << a1 << std::endl;
    std::cout << "a1.abs() =" << std::endl
                << a1.abs() << std::endl;
    std::cout << "a1.abs().sqrt() =" << std::endl
                << a1.abs().sqrt() << std::endl;
    std::cout << "a1.min(a1.abs().sqrt()) =" << std::endl
                << a1.min(a1.abs().sqrt()) << std::endl;
    
    /// array matrix
    Eigen::MatrixXf m1(2,2);
    Eigen::MatrixXf n(2,2);
    Eigen::MatrixXf result(2,2);
    
    m1 << 1,2,
        3,4;
    n << 5,6,
        7,8;
    
    result = m1 * n;
    std::cout << "-- Matrix m1*n: --\n" << result << "\n\n";
    result = m1.array() * n.array();
    std::cout << "-- Array m1*n: --\n" << result << "\n\n";
    result = m1.cwiseProduct(n);
    std::cout << "-- With cwiseProduct: --\n" << result << "\n\n";
    result = m1.array() + 4;
    std::cout << "-- Array m1 + 4: --\n" << result << "\n\n";
    result = m1 + n;
    std::cout << "-- Matrix m1 + n: --\n" << result << "\n\n";

    Eigen::MatrixXf m2(2,2);
    Eigen::MatrixXf n2(2,2);
    Eigen::MatrixXf result2(2,2);
    
    m2 << 1,2,
        3,4;
    n2 << 5,6,
        7,8;
    
    result2 = (m2.array() + 4).matrix() * m2;
    std::cout << "-- Combination 1: --\n" << result2 << "\n\n";
    result2 = (m2.array() * n2.array()).matrix() * m2;
    std::cout << "-- Combination 2: --\n" << result2 << "\n\n";

}