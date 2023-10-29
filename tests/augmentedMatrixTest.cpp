#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"

TEST(AugmentedMatrixTest, EqualRowColumn) {
    // Given
    Matrix<Fraction> matrix(3);
    std::istringstream input_matrix(
            "1 5 9\n"
            "2 6 10\n"
            "3 7 11\n"
    );

    // When
    input_matrix >> matrix;
    matrix = get_augmented(matrix);
    std::ostringstream actual_entries;
    actual_entries << matrix;
    std::ostringstream expected_entries(
            "1 5 9 1 0 0\n"
            "2 6 10 0 1 0\n"
            "3 7 11 0 0 1\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}
