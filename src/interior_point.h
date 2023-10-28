#ifndef ASSIGNMENT_2_INTERIOR_POINT_H
#define ASSIGNMENT_2_INTERIOR_POINT_H

#include "matrix.h"
#include "gaussianElim.h"
#include "vector_ops.h"
#include "matrix_ops.h"
#include "usefulEnums.h"

#define MAX_INIT_NUMBER 100.0

template<typename T>
class InteriorPoint {
private:
    Objective obj;
    std::vector<T> c;
    Matrix<T> A;
    std::vector<T> b;
    T accuracy;
    T alpha;
    std::vector<size_t> basic;

    Matrix<T> D;
    Matrix<T> P;
    Matrix<T> A_;
    std::vector<T> solution;
    std::vector<T> solution_;
    std::vector<T> c_;
    std::vector<T> cp;

    void clear_solution() {
        for (T& num : solution) {
            num = 0;
        }
    }

    bool initial_solution_validation() {
        for (size_t i = 0; i < A.get_rows(); i++) {
            T value = 0;
            for (size_t j = 0; j < A.get_columns(); j++) {
                value += A[i][j] * solution[j];
            }
            if (value != b[i]) {
                return false;
            }
        }
        return true;
    }

    std::vector<size_t> sort_basis_by_rows() {
        std::vector<size_t> sorted_by_rows;
        for (size_t basis_var_col : basic) {
            for (size_t i = 0; i < A.get_rows(); i++) {
                if (A[i][basis_var_col] == 1) {
                    sorted_by_rows.push_back(i);
                    break;
                }
            }
        }
        std::vector<size_t> basis_by_rows(sorted_by_rows.size());
        for (size_t i = 0; i < sorted_by_rows.size(); i++) {
            basis_by_rows[sorted_by_rows[i]] = basic[i];
        }
        return basis_by_rows;
    }

    bool contains_in_basis(size_t index) {
        bool is_found = false;
        for (size_t i : basic) {
            if (i == index) is_found = true;
        }
        return is_found;
    }

    void pseudo_random_initial_solution(T initial_value, const std::vector<size_t> &sorted_by_rows) {
        clear_solution();

        // Suppose that non-basic variables equal to initial_value
        for (size_t i = 0; i < solution.size(); i++) {
            if (contains_in_basis(i)) continue;
            solution[i] = initial_value;
        }
        // Find all the basic variables
        size_t index = 0;
        for (size_t i = 0; i < A.get_rows(); i++) {
            T value = b[i];
            for (size_t j = 0; j < A.get_columns(); j++) {
                value -= A[i][j] * solution[j];
            }
            solution[sorted_by_rows[index]] = value / A[i][sorted_by_rows[index]];
            index++;
        }
    }

    void impossible_to_find_initial() {
        std::cout << "Sorry, but it is impossible to find initial solution!\n"
                     "If you can, input the initial solution by yourself\n"
                     "If not, just try to input another values. Thank you\n"
                     "Length of the input is " << solution.size() << std::endl;
    }

    void wait_for_user_initial_solution() {
        for (auto &i: solution) {
            std::cin >> i;
        }
    }

    void initial_step() {
        std::vector<size_t> basis_sorted_by_rows = sort_basis_by_rows();

        bool is_initial_solution_found = false;
        for (T init = 0.1; init < MAX_INIT_NUMBER; init += 0.1) {
            pseudo_random_initial_solution(init, basis_sorted_by_rows);
            is_initial_solution_found = initial_solution_validation();
            if (is_initial_solution_found) break;
        }

        if (!is_initial_solution_found) {
            impossible_to_find_initial();
            wait_for_user_initial_solution();
        }

        fill_D();
    }

    void fill_D() {
        for (size_t i = 0; i < D.get_rows(); i++) {
            D[i][i] = solution[i];
        }
    }

    void calculate_p() {
        Matrix<T> I = get_identity<T>(D.get_rows(), D.get_rows());
        Matrix<T> A_t = A_.transpose();
        GaussianElimination elimination(A_ * A_t);
        Matrix<T> A_inverse = elimination.get_inverse_matrix();
        P = I - A_t * A_inverse * A_;
    }

    T find_max_abs() {
        T max = 0;
        for (T value: cp) {
            if (value < 0) {
                if (abs(value) > max) max = abs(value);
            }
        }
        return max;
    }

    void calculate_new_x(T max) {
        T factor = alpha / max;
        for (size_t i = 0; i < solution_.size(); i++) {
            solution_[i] = 1.0 + factor * cp[i];
        }
    }

    bool iterate() {
        // Step 2
        A_ = A * D;
        c_ = multiply(D, c);

        // Step 3
        calculate_p();
        cp = multiply(P, c_);

        // Step 4
        T maxNeg = find_max_abs();
        calculate_new_x(maxNeg);
        solution_ = multiply(D, solution_);
        if (norm(subtraction(solution_, solution)) < accuracy) {
            solution = solution_;
            return false;
        }

        // Step 5 --> 1
        solution = solution_;
        fill_D();
        return true;
    }

    double norm(std::vector<T> vector) {
        double sum = 0;
        for (auto val: vector) {
            auto valD = static_cast<double>(val);
            sum += pow(valD, 2);
        }
        return sqrt(sum);
    }

    T abs(const T &value) {
        return value < 0 ? value * -1 : value;
    }

    void invert_coefficients() {
        for (T& coefficient : c) {
            coefficient *= -1;
        }
    }

    void print() {
        std::cout << "Iteration\nD\n" << D << std::endl;
        std::cout << "A\n" << A << std::endl;
        std::cout << "c_\n";
        for (auto num: c_) {
            std::cout << num << " ";
        }
        std::cout << "\n\n";
        std::cout << "P\n" << P << std::endl;
        std::cout << "cp\n";
        for (auto num: cp) {
            std::cout << num << " ";
        }
        std::cout << "\n\n";
    }

public:
    InteriorPoint(const Objective &obj,
                  const std::vector<T> &coefficients,
                  const Matrix<T> &A,
                  const std::vector<T> &b,
                  const T &accuracy,
                  const T &alpha,
                  const std::vector<size_t> &basic) :
            obj(obj), c(coefficients), A(A), b(b),
            accuracy(accuracy),alpha(alpha), basic(basic),
            D(coefficients.size()), P(coefficients.size()),
            A_(A.get_rows(), A.get_columns()), solution(coefficients.size()),
            solution_(coefficients.size()), c_(coefficients.size()), cp(coefficients.size()) {
        D = get_identity<T>(coefficients.size(), coefficients.size());
        if (obj == 0) invert_coefficients();
    }

    std::vector<T> solve() {
        initial_step();
        while (iterate());
        return solution;
    }

    T get_found_optimum() {
        T optimum = dot_product(c, solution);
        return (obj == MIN ? optimum * -1 : optimum);
    }

    void form_answer() {
        std::cout << "Solution of the Interior point algorithm when alpha = " << alpha
        << "\nDecision variables vector: X = [";
        for (size_t i = 0; i < solution.size(); i++) {
            if (i == solution.size() - 1) {
                std::cout << solution[i] << "]";
                break;
            }
            std::cout << solution[i] << ", ";
        }
        T optimum = get_found_optimum();
        std::cout << "    =>    Optimum = " << optimum << std::endl;
    }
};

#endif //ASSIGNMENT_2_INTERIOR_POINT_H
