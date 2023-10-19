#ifndef ASSIGNMENT_2_INTERIOR_POINT_H
#define ASSIGNMENT_2_INTERIOR_POINT_H

#include "matrix.h"
#include "gaussianElim.h"
#include "vector_ops.h"
#include "matrix_ops.h"

enum Objective {
    MIN, MAX
};

template<typename T>
class InteriorPoint {
private:
    Objective obj;
    std::vector<T> c;
    Matrix<T> A;
    std::vector<T> b;
    T accuracy;
    T alpha;

    Matrix<T> D;
    Matrix<T> P;
    Matrix<T> A_;
    std::vector<T> solution;
    std::vector<T> solution_;
    std::vector<T> c_;
    std::vector<T> cp;

    void initialStep() {
        // TODO: Properly obtain the initial solution for the problem (automatically)
        solution = {0.5, 3.5, 1, 2};
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
            solution_[i] = 1 + factor * cp[i];
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

public:
    InteriorPoint(const Objective &obj,
                  const std::vector<T> &coefficients,
                  const Matrix<T> &A,
                  const std::vector<T> &b,
                  const T &accuracy,
                  const T &alpha) :
            obj(obj), c(coefficients), A(A), b(b),
            accuracy(accuracy), alpha(alpha), D(coefficients.size()), P(coefficients.size()),
            A_(A.get_rows(), A.get_columns()), solution(coefficients.size()),
            solution_(coefficients.size()), c_(coefficients.size()), cp(coefficients.size()) {
        D = get_identity<T>(coefficients.size(), coefficients.size());
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
        std::cout << "\n";
    }

    std::vector<T> solve() {
        initialStep();
        while (iterate());
        return solution;
    }
};

#endif //ASSIGNMENT_2_INTERIOR_POINT_H
