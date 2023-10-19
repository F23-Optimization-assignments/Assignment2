#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"
#include "../src/gaussianElim.h"

TEST(MatrixDetTest, NotZeroDetIdentity) {
    // Given
    Matrix<Fraction> matrix = get_identity<Fraction>(3, 3);
    GaussianElimination<Fraction> gaussianElimination(matrix);

    // When
    Fraction actual_value = gaussianElimination.determinant();
    Fraction expected_value = 1;


    // Then
    ASSERT_EQ(actual_value, expected_value);
}

TEST(MatrixDetTest, NotZeroDet) {
    // Given
    Matrix<Fraction> matrix(3, 3);
    std::istringstream input_matrix(
            "5 3 9\n"
            "22 87 1\n"
            "5 43 2\n"
    );

    // When
    input_matrix >> matrix;
    GaussianElimination<Fraction> gaussianElimination(matrix);
    Fraction actual_value = gaussianElimination.determinant();
    Fraction expected_value = 5137;


    // Then
    ASSERT_EQ(actual_value, expected_value);
}

TEST(MatrixDetTest, ZeroDet) {
    // Given
    Matrix<Fraction> matrix(3, 3);
    std::istringstream input_matrix(
            "1 2 3\n"
            "4 5 6\n"
            "7 8 9\n"
    );

    // When
    input_matrix >> matrix;
    try {
        GaussianElimination<Fraction> gaussianElimination(matrix);
        Fraction actual_value = gaussianElimination.determinant();
        FAIL();
    } catch (std::exception& ex) {
        // Then
        EXPECT_STREQ("Matrix is singular", ex.what());
    }
}

