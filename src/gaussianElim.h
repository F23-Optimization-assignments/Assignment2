#ifndef ASSIGNMENT_2_GAUSSIANELIM_H
#define ASSIGNMENT_2_GAUSSIANELIM_H

#include "matrix.h"
#include "matrix_ops.h"

template<typename T>
class GaussianElimination {
private:
    Matrix<T> original_matrix;
    Matrix<T> inverse_matrix;
    Matrix<T> augmented_matrix;
    Matrix<T> permutation_matrix;
    size_t size;

    void row_subtraction(size_t row_to_be_subtracted, size_t row_to_subtract, T times) {
        for (size_t i = 0; i < augmented_matrix.get_columns(); i++) {
            augmented_matrix[row_to_be_subtracted][i] -= augmented_matrix[row_to_subtract][i] * times;
        }
    }

    T abs(const T &value) {
        return value < 0 ? value * -1 : value;
    }

    void exchange_rows(size_t index_1, size_t index_2) {
        permutation_matrix[index_1][index_1] = 0;
        permutation_matrix[index_1][index_2] = 1;

        permutation_matrix[index_2][index_2] = 0;
        permutation_matrix[index_2][index_1] = 1;
    }

    int permutation_index(size_t current_upper_row, size_t current_col) {
        T max = abs(augmented_matrix[current_upper_row][current_col]);
        int max_index = -1;

        for (size_t i = current_upper_row; i < size; i++) {
            T current = abs(augmented_matrix[i][current_col]);
            if (max < current) {
                max = current;
                max_index = (int) i;
            }
        }

        return max_index;
    }

    void direct_way() {
        for (size_t j = 0; j < size - 1; j++) {
            bool permutation_flag = false;
            int index;
            for (size_t i = j + 1; i < size; i++) {
                if ((index = permutation_index(j, j)) != -1 && !permutation_flag) {
                    permutation_flag = true;
                    permutation_matrix = get_identity<T>(size, size);
                    exchange_rows(j, index);
                    augmented_matrix = permutation_matrix * augmented_matrix;
                }

                T times = augmented_matrix[i][j] / augmented_matrix[j][j];

                if (times == 0) {
                    continue;
                }

                row_subtraction(i, j, times);
            }
        }
    }

    void way_back() {
        for (int j = size - 1; j > 0; j--) {
            for (int i = j - 1; i >= 0; i--) {
                T times = augmented_matrix[i][j] / augmented_matrix[j][j];
                if (times == 0) {
                    continue;
                }

                row_subtraction(i, j, times);
            }
        }
    }

    void normalisation() {
        for (size_t i = 0; i < size; i++) {
            T factor = augmented_matrix[i][i];
            for (size_t j = 0; j < augmented_matrix.get_columns(); j++) {
                augmented_matrix[i][j] /= factor;
            }
        }
    }

    void augmented_to_inverse() {
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                inverse_matrix[i][j] = augmented_matrix[i][j + size];
            }
        }
    }

    void reinitialise() {
        augmented_matrix = get_augmented(original_matrix);
    }

    void check_criteria() {
        if (original_matrix.get_rows() != original_matrix.get_columns()) {
            throw MatrixException("not square augmented matrix provided for inverse process");
        }
        if (determinant() == 0) {
            throw MatrixException("Matrix is singular");
        }
    }

public:
    explicit GaussianElimination(const Matrix<T> &matrix) :
            original_matrix(matrix),
            inverse_matrix(matrix.get_rows()),
            augmented_matrix(get_augmented(matrix)),
            permutation_matrix(get_identity<T>(matrix.get_rows(), matrix.get_rows())),
            size(matrix.get_rows()) {
        check_criteria();
    }

    Matrix<T> get_inverse_matrix() {
        reinitialise();
        direct_way();
        way_back();
        normalisation();
        augmented_to_inverse();
        return inverse_matrix;
    }

    T determinant() {
        reinitialise();
        Matrix temp(original_matrix);
        int index;
        int permutation_count = 0;
        for (size_t j = 0; j < size - 1; j++) {
            bool permutation_flag = false;
            for (size_t i = j + 1; i < size; i++) {
                if ((index = permutation_index(j, j)) != -1 && !permutation_flag) {
                    permutation_flag = true;
                    permutation_count++;
                    permutation_matrix = get_identity<T>(size, size);
                    exchange_rows(j, index);
                    temp = permutation_matrix * temp;
                }
                T times = temp[i][j] / temp[j][j];

                for (size_t k = 0; k < size; k++) {
                    temp[i][k] -= temp[j][k] * times;
                }
            }
        }

        T det = permutation_count > 0 ? -1 : 1;
        for (size_t i = 0; i < size; i++) {
            det *= temp[i][i];
        }

        return det;
    }

    std::vector<T> solve(const std::vector<T> &rhs_values) {
        augmented_matrix = get_augmented_RHS(original_matrix, rhs_values);
        direct_way();
        way_back();
        std::vector<T> solution(size);
        for (size_t i = 0; i < size; i++) {
            solution[i] = augmented_matrix[i][size] / augmented_matrix[i][i];
        }
        return solution;
    }
};

#endif //ASSIGNMENT_2_GAUSSIANELIM_H
