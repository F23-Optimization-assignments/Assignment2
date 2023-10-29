#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"

TEST(MatrixTransposeTest, RowGreaterThanColumn) {
    // Given
    Matrix<Fraction> matrix(3, 4);
    std::istringstream input_matrix(
            "1 2 3 4\n"
            "5 6 7 8\n"
            "9 10 11 12\n"
    );

    // When
    input_matrix >> matrix;
    std::ostringstream actual_entries;
    actual_entries << matrix.transpose();
    std::ostringstream expected_entries(
            "1 5 9\n"
            "2 6 10\n"
            "3 7 11\n"
            "4 8 12\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}

TEST(MatrixTransposeTest, ColumnGreaterThanRow) {
    // Given
    Matrix<Fraction> matrix(4, 3);
    std::istringstream input_matrix(
            "1 5 9\n"
            "2 6 10\n"
            "3 7 11\n"
            "4 8 12\n"
    );

    // When
    input_matrix >> matrix;
    std::ostringstream actual_entries;
    actual_entries << matrix.transpose();
    std::ostringstream expected_entries(
            "1 2 3 4\n"
            "5 6 7 8\n"
            "9 10 11 12\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}

TEST(MatrixTransposeTest, EqualRowColumn) {
    // Given
    Matrix<Fraction> matrix(3);
    std::istringstream input_matrix(
            "1 5 9\n"
            "2 6 10\n"
            "3 7 11\n"
    );

    // When
    input_matrix >> matrix;
    std::ostringstream actual_entries;
    actual_entries << matrix.transpose();
    std::ostringstream expected_entries(
            "1 2 3\n"
            "5 6 7\n"
            "9 10 11\n"
    );

    // Then
    ASSERT_EQ(actual_entries.str(), expected_entries.str());
}
