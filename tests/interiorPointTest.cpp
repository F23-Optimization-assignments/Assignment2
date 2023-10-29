#include <gtest/gtest.h>
#include <sstream>
#include "../src/matrix.h"
#include "../src/fraction.h"
#include "../src/matrix_ops.h"
#include "../src/gaussianElim.h"
#include "../src/interior_point.h"
#include "../src/simplex.h"

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

TEST(InteriorPointTest, ExampleFromAss2_2) {
// Given
    size_t vars = 7, cons = 3;
    std::vector<double> coeffs = {8, 6, 3, -2, 0, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "1 2 2 4 1 0 0\n2 -1 1 2 0 1 0\n4 -2 1 -1 0 0 1\n"
    );
    std::vector<double> b = {40, 8, 10};
    std::vector<size_t> basic = {4, 5, 6};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MAX, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = 170;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, MinFind_1) {
// Given
    size_t vars = 6, cons = 3;
    std::vector<double> coeffs = {-2, 3, -6, -1, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 1 -2 1 0 0\n1 2 4 0 1 0\n1 -1 2 0 0 1"
    );
    std::vector<double> b = {24, 22, 10};
    std::vector<size_t> basic = {3, 4, 5};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MIN, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = -64;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, MinFind_2) {
// Given
    size_t vars = 6, cons = 2;
    std::vector<double> coeffs = {-6, -8, -5, -9, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 1 1 3 1 0\n1 3 1 2 0 1\n"
    );
    std::vector<double> b = {5, 3};
    std::vector<size_t> basic = {4, 5};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MIN, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = -40;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, MinFind_3) {
// Given
    size_t vars = 6, cons = 4;
    std::vector<double> coeffs = {-2, -1, 0, 0, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 1 1 0 0 0\n2 3 0 1 0 0\n4 1 0 0 1 0\n1 5 0 0 0 1"
    );
    std::vector<double> b = {4, 3, 5, 1};
    std::vector<size_t> basic = {2, 3, 4, 5};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MIN, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = -2;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, MinFind_4_unbounded) {
// Given
    size_t vars = 4, cons = 2;
    std::vector<double> coeffs = {-2, -1, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "1 -1 1 0\n2 0 0 1"
    );
    std::vector<double> b = {10, 40};
    std::vector<size_t> basic = {2, 3};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MIN, coeffs, A, b, PRECISE, accuracy, basic);
    try {
        algorithm.solve();
    } catch (MatrixException &e) {
        SUCCEED();
        return;
    }
    FAIL();
}

TEST(InteriorPointTest, ExampleFromReport1) {
// Given
    size_t vars = 5, cons = 2;
    std::vector<double> coeffs = {-4, 12, 0, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 2 4 1 0\n2 -2 3 0 1"
    );
    std::vector<double> b = {2, 1};
    std::vector<size_t> basic = {3, 4};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MIN, coeffs, A, b, PRECISE, accuracy, basic);
    algorithm.solve();
    double actualValue = algorithm.get_found_optimum();
    double expectedValue = -2;

// Then
    assert_approx_eq(actualValue, expectedValue);
}

TEST(InteriorPointTest, ExampleFromReport2) {
// Given
    size_t vars = 6, cons = 2;
    std::vector<double> coeffs = {-4, -5, 0, 0, 0, 0};
    Matrix<double> A(cons, vars);
    std::istringstream input_matrix(
            "2 3 -1 0 1 0\n8 6 0 -1 0 1"
    );
    std::vector<double> b = {8, 9};
    std::vector<size_t> basic = {4, 5};
    double accuracy = 0.5;

// When
    input_matrix >> A;
    InteriorPoint algorithm(MIN, coeffs, A, b, PRECISE, accuracy, basic);
    try {
        algorithm.solve();
    } catch (MatrixException &e) {
        SUCCEED();
        return;
    }
    FAIL();
}