#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"
#include "../src/gaussianElim.h"
#include "../src/interior_point.h"

#define PRECISE 0.00001

TEST(InteriorPointTest, Lab6_1) {
// Given
    size_t vars = 4, cons = 2;
    std::vector<double> coeffs = {1, 1, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 4 1 0\n"
            "1 3 0 -1\n"
    );
    std::vector<double> b = {16, 9};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MAX, coeffs, A, b, PRECISE, accuracy);
    std::vector<double> actualSolution = algorithm.solve();
    std::vector<double> expectedSolution = {6, 1, 1.7854e-06, 1.7854e-06};

// Then
    for (size_t i = 0; i < actualSolution.size(); i++) {
        if (fabs(actualSolution[i] - expectedSolution[i]) > PRECISE) FAIL();
    }
    SUCCEED();
}