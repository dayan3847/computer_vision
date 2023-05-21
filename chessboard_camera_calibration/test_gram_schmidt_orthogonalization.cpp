#include <iostream>
#include <Eigen/Dense>

int main() {
    // Ejemplo 3x3

    Eigen::MatrixXd A(3, 3);
    A
            <<
            2, 1, 2,
            1, 0, -3,
            1, 10, 11;

    Eigen::MatrixXd Q = A.householderQr().householderQ();

    std::cout << "Matriz A:\n" << A << "\n\n";
    std::cout << "Matriz Q (Ortogonalizada):\n" << Q << "\n\n";


    // Ejemplo 2x2

    Eigen::MatrixXd B(2, 2);
    B
            <<
            2, 1,
            1, 4;

    Eigen::MatrixXd Q2 = B.householderQr().householderQ();

    std::cout << "Matriz B:\n" << B << "\n\n";
    std::cout << "Matriz Q2 (Ortogonalizada):\n" << Q2 << "\n\n";

    return 0;
}
