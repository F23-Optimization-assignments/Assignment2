#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"
#include "../src/gaussianElim.h"

TEST(SolveLinearEqTest, IdentityMatrix) {
// Given
    Matrix<Fraction> matrix = get_identity<Fraction>(3, 3);
    std::vector<Fraction> values{3, 15, 14};


// When
    GaussianElimination<Fraction> gaussianElimination(matrix);
    std::vector<Fraction> solution = gaussianElimination.solve(values);
    std::ostringstream actual_entries;
    for (auto i: solution) {
        actual_entries << i << " ";
    }
    std::ostringstream expected_entries(
            "3 15 14 "
    );

// Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}

TEST(InverseMatrixTest, RandomMatrix) {
// Given
    Matrix<Fraction> matrix(3, 3);
    std::istringstream input_matrix(
            "3 2 -4\n"
            "2 3 3\n"
            "5 -3 1\n"
    );
    std::vector<Fraction> values{3, 15, 14};

// When
    input_matrix >> matrix;
    GaussianElimination<Fraction> gaussianElimination(matrix);
    std::vector<Fraction> solution = gaussianElimination.solve(values);
    std::ostringstream actual_entries;
    for (auto i: solution) {
        actual_entries << i << " ";
    }
    std::ostringstream expected_entries(
            "3 1 2 "
    );

// Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}
