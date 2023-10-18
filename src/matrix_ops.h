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
    if (rows != columns) throw MatrixException("count of size not equal to count of size");
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

#endif //ASSIGNMENT_2_MATRIX_OPS_H
