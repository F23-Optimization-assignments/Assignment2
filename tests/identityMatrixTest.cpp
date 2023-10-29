#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"

TEST(IdentityMatrixTest, RowGreaterThanColumn) {
    // Given
    Matrix<Fraction> matrix(3, 4);

    // When
    matrix = get_identity<Fraction>(3, 4);
    std::ostringstream actual_entries;
    actual_entries << matrix;
    std::ostringstream expected_entries(
            "1 0 0 0\n"
            "0 1 0 0\n"
            "0 0 1 0\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}

TEST(IdentityMatrixTest, ColumnGreaterThanRow) {
    // Given
    Matrix<Fraction> matrix(4, 3);

    // When
    matrix = get_identity<Fraction>(4, 3);
    std::ostringstream actual_entries;
    actual_entries << matrix;
    std::ostringstream expected_entries(
            "1 0 0\n"
            "0 1 0\n"
            "0 0 1\n"
            "0 0 0\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}

TEST(IdentityMatrixTest, EqualRowColumn) {
    // Given
    Matrix<Fraction> matrix(3);

    // When
    matrix = get_identity<Fraction>(3, 3);
    std::ostringstream actual_entries;
    actual_entries << matrix;
    std::ostringstream expected_entries(
            "1 0 0\n"
            "0 1 0\n"
            "0 0 1\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}