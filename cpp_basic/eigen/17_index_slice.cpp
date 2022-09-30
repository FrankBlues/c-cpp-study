#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>


// Custom index list
struct pad {
  Eigen::Index size() const { return out_size; }
  Eigen::Index operator[] (Eigen::Index i) const { return std::max<Eigen::Index>(0,i-(out_size-in_size)); }
  Eigen::Index in_size, out_size;
};


int main()
{
    std::vector<int> ind{4,2,5,5,3};
    Eigen::MatrixXi A = Eigen::MatrixXi::Random(4,6);
    std::cout << "Initial matrix A:\n" << A << "\n\n";
    std::cout << "A(all,ind):\n" << A(Eigen::all,ind) << "\n\n";

    std::cout << "A(all,{4,2,5,5,3}):\n" << A(Eigen::all,{4,2,5,5,3}) << "\n\n";


    Eigen::ArrayXi ind1(5); ind1<<4,2,5,5,3;
    std::cout << "A(all,ind-1):\n" << A(Eigen::all,ind1-1) << "\n\n";

    
    Eigen::Matrix3i A1;
    A1.reshaped() = Eigen::VectorXi::LinSpaced(9,1,9);
    std::cout << "Initial matrix A1:\n" << A1 << "\n\n";
    Eigen::MatrixXi B(5,5);
    B = A1(pad{3,5}, pad{3,5});
    std::cout << "A(pad{3,N}, pad{3,N}):\n" << B << "\n\n";

    return 0;
}
