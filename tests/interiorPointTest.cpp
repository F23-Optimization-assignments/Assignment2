#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"
#include "../src/gaussianElim.h"
#include "../src/interior_point.h"

#define PRECISE 0.00001
#define ANSWERS_DIVERGENCE 0.5

template <typename T>
void assert_approx_eq(T val1, T val2) {
    if (fabs(val1 - val2) > ANSWERS_DIVERGENCE) FAIL();
    SUCCEED();
}

TEST(InteriorPointTest, MaxFind_1) {
// Given
    size_t vars = 4, cons = 2;
    std::vector<double> coeffs = {1, 1, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 4 1 0\n"
            "1 3 0 1\n"
    );
    std::vector<double> b = {16, 9};
    std::vector<size_t> basic = {2, 3};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MAX, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = 8.0;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, MaxFind_1_changedColumns) {
// Given
    size_t vars = 4, cons = 2;
    std::vector<double> coeffs = {1, 0, 1, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 1 4 0\n"
            "1 0 3 1\n"
    );
    std::vector<double> b = {16, 9};
    std::vector<size_t> basic = {1, 3};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MAX, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = 8.0;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, MaxFind_2) {
// Given
    size_t vars = 7, cons = 3;
    std::vector<double> coeffs = {2, 1, -3, 5, 0, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "1 2 2 4 1 0 0\n"
            "2 -1 1 2 0 1 0\n"
            "4 -2 1 -1 0 0 1\n"
    );
    std::vector<double> b = {40, 8, 10};
    std::vector<size_t> basic = {4, 5, 6};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MAX, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = 41;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, MaxFind_3) {
// Given
    size_t vars = 6, cons = 3;
    std::vector<double> coeffs = {9, 10, 16, 0, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "18 15 12 1 0 0\n"
            "6 4 8 0 1 0\n"
            "5 3 3 0 0 1\n"
    );
    std::vector<double> b = {360, 192, 180};
    std::vector<size_t> basic = {3, 4, 5};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MAX, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = 400;

// Then
    assert_approx_eq(actualValue, expectedValue);
}