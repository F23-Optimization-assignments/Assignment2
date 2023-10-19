#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"
#include "../src/gaussianElim.h"

TEST(InverseMatrixTest, IdentityMatrix) {
    // Given
    Matrix<Fraction> matrix = get_identity<Fraction>(3, 3);

    // When
    GaussianElimination<Fraction> gaussianElimination(matrix);

    std::ostringstream actual_entries;
    actual_entries << gaussianElimination.get_inverse_matrix();
    std::ostringstream expected_entries(
            "1 0 0\n"
            "0 1 0\n"
            "0 0 1\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}

TEST(InverseMatrixTest, RandMatrix) {
    // Given
    Matrix<Fraction> matrix(3, 3);
    std::istringstream input_matrix(
            "5 7 9\n"
            "4 3 8\n"
            "7 5 6\n"
    );

    // When
    input_matrix >> matrix;
    GaussianElimination<Fraction> gaussianElimination(matrix);

    std::ostringstream actual_entries;
    actual_entries << gaussianElimination.get_inverse_matrix();
    std::ostringstream expected_entries(
            "-22/105 1/35 29/105\n"
            "32/105 -11/35 -4/105\n"
            "-1/105 8/35 -13/105\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}

TEST(InverseMatrixTest, RandomMatrixLarge) {
    // Given
    Matrix<Fraction> matrix(4, 4);
    std::istringstream input_matrix(
            "2 4 5 2\n"
            "8 9 5 1\n"
            "0 3 2 1\n"
            "1 3 5 7\n"
    );

    // When
    input_matrix >> matrix;
    GaussianElimination<Fraction> gaussianElimination(matrix);
    std::ostringstream actual_entries;
    actual_entries << gaussianElimination.get_inverse_matrix();
    std::ostringstream expected_entries(
            "0 3/25 -2/5 1/25\n"
            "-1/4 19/300 29/60 -1/150\n"
            "1/2 -17/150 -7/30 -7/75\n"
            "-1/4 11/300 1/60 31/150\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}
