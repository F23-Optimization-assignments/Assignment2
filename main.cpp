#include "src/matrix.h"
#include "gaussianElim.h"
#include "fraction.h"

int main() {
    // Given
    Matrix<Fraction> matrix(3);
    std::cin >> matrix;

    // When
    GaussianElimination<Fraction> gaussianElimination(matrix);

    std::cout << gaussianElimination.determinant() << '\n';
    std::cout << gaussianElimination.get_inverse_matrix() << '\n';

    return EXIT_SUCCESS;
}

