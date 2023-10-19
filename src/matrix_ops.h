#ifndef ASSIGNMENT_2_MATRIX_OPS_H
#define ASSIGNMENT_2_MATRIX_OPS_H

#include "matrix.h"

template<typename T>
Matrix<T> get_identity(const size_t& rows, const size_t& columns) {
    Matrix<T> matrix(rows, columns);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            matrix[i][j] = 0;
            if (i == j) matrix[i][j] = 1;
        }
    }
    return matrix;
}

template<typename T>
Matrix<T> get_augmented(const Matrix<T>& matrix) {
    size_t rows = matrix.get_rows(), columns = matrix.get_columns();
    if (rows != columns) throw MatrixException("count of rows not equal to count of columns");
    Matrix<T> identity = get_identity<T>(rows, columns);
    Matrix<T> augmented(rows, columns * 2);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            augmented[i][j] = matrix[i][j];
            augmented[i][j + columns] = identity[i][j];
        }
    }
    return augmented;
}

template<typename T>
Matrix<T> get_augmented_RHS(Matrix<T>& matrix, const std::vector<T>& rhs_values) {
    size_t rows = matrix.get_rows(), columns = matrix.get_columns();
    if (rows != rhs_values.size()) throw MatrixException("incorrect dimension between matrix and vector");
    Matrix<T> augmented_rhs(rows, columns + 1);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            augmented_rhs[i][j] = matrix[i][j];
        }
        augmented_rhs[i][columns] = rhs_values[i];
    }
    return augmented_rhs;
}

template<typename T>
std::vector<T> multiply(const Matrix<T>& matrix, const std::vector<T>& vector) {
    size_t rows = matrix.get_rows(), columns = matrix.get_columns();
    if (columns != vector.size()) throw MatrixException("incorrect dimension between matrix and vector");
    std::vector<T> mult(columns);
    for (size_t i = 0; i < rows; i++) {
        T rowIter = 0;
        for (size_t j = 0; j < columns; j++) {
            rowIter += matrix[i][j] * vector[j];
        }
        mult[i] = rowIter;
    }
    return mult;
}

#endif //ASSIGNMENT_2_MATRIX_OPS_H
