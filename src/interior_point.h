#ifndef ASSIGNMENT_2_INTERIOR_POINT_H
#define ASSIGNMENT_2_INTERIOR_POINT_H

#include "matrix.h"

enum Objective {
    MIN, MAX
};

template<typename T>
class InteriorPoint {
private:
    Objective obj;
    std::vector<T> func;
    Matrix<T> A;
    std::vector<T> b;
    T accuracy;
    std::vector<size_t> basic_indices;

public:
    InteriorPoint(const Objective &obj,
            const std::vector<T> &coefficients,
            const Matrix<T> &A,
            const std::vector<T> &b,
            const T& accuracy) : obj(obj), func(
            coefficients), A(A), b(b), basic_indices(
            basic_indices), accuracy(accuracy) {
    }
};

#endif //ASSIGNMENT_2_INTERIOR_POINT_H
