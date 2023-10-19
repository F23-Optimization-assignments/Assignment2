#include"src/matrix.h"
#include "gaussianElim.h"
#include "fraction.h"
#include "interior_point.h"

int main() {
    // Input number of ALL variables and constraints
    size_t vars, cons;
    std::cin >> vars >> cons;


    // Input function's coefficients
    std::vector<double> coeffs(vars);
    for (auto &i: coeffs) {
        std::cin >> i;
    }

    // Input matrix A of constraints
    Matrix<double> A(cons, vars);
    std::cin >> A;

    // Input vector of values of constraints
    std::vector<double> b(cons);
    for (auto &i: b) {
        std::cin >> i;
    }

    // Input the approximation accuracy
    double accuracy;
    std::cin >> accuracy;

    InteriorPoint<double> algorithm(MAX, coeffs, A, b, accuracy, 0.5);
    std::vector<double> solution = algorithm.solve();

    for (auto i : solution) {
        std::cout << i << " ";
    }

    return EXIT_SUCCESS;
}

/*

4 2
1 1 0 0
2 4 1 0
1 3 0 -1
16 9
0.00001

 */

