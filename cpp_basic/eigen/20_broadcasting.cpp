#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace std;
int main()
{
  Eigen::MatrixXf mat(2,4);
  Eigen::VectorXf v(2);
  Eigen::VectorXf v1(4);
  
  mat << 1, 2, 6, 9,
         3, 1, 7, 2;
         
  v << 0,
       1;
       
  //add v to each column of m
  mat.colwise() += v;
  
  std::cout << "Broadcasting result: " << std::endl;
  std::cout << mat << std::endl;

  v1 << 0,1,2,3;

  //add v to each row of m
  mat.rowwise() += v1.transpose();
  
  std::cout << "Broadcasting result: " << std::endl;
  std::cout << mat << std::endl;

  /// Combining broadcasting with other operations
  Eigen::Index index;
  // find nearest neighbour
  (mat.colwise() - v).colwise().squaredNorm().minCoeff(&index);

  std::cout << "Nearest neighbour is column " << index << ":" << std::endl;
  std::cout << mat.col(index) << std::endl;
}