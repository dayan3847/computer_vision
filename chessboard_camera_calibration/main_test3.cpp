#include <iostream>
#include <Eigen/Dense>

int main()
{
    Eigen::MatrixXd A(3, 3);
    A << 1, 1, 0,
         -1, 1, 1,
         2, 2, 1;

    Eigen::MatrixXd Q = A.householderQr().householderQ();

    std::cout << "Matriz A:\n" << A << "\n\n";
    std::cout << "Matriz Q (Ortogonalizada):\n" << Q << "\n\n";

    return 0;
}
