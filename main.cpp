#include"src/matrix.h"
#include "gaussianElim.h"
#include "fraction.h"
#include "interior_point.h"
#include "simplex.h"

int main() {
    // Input type of problem - min (0) OR max (1)
    int objNum;
    std::cin >> objNum;
    auto obj = static_cast<Objective>(objNum);

    // Input number of ALL variables and constraints
    size_t vars, cons;
    std::cin >> vars >> cons;

    // Input function's coefficients
    std::vector<Fraction> coeffs_frac(vars);
    for (auto &i: coeffs_frac) {
        std::cin >> i;
    }
    std::vector<double> coeffs_double(vars);
    for (size_t i = 0; i < vars; i++) {
        coeffs_double[i] = (double) coeffs_frac[i];
    }

    // Input matrix A of constraints
    Matrix<Fraction> A_frac(cons, vars);
    std::cin >> A_frac;
    Matrix<double> A_double(cons, vars);
    for (size_t i = 0; i < cons; i++) {
        for (size_t j = 0; j < vars; j++) {
            A_double[i][j] = (double) A_frac[i][j];
        }
    }

    // Input vector of values of constraints
    std::vector<Fraction> b_frac(cons);
    for (auto &i: b_frac) {
        std::cin >> i;
    }
    std::vector<double> b_double(cons);
    for (size_t i = 0; i < cons; i++) {
        b_double[i] = (double) b_frac[i];
    }

    // Input indices of initial basic vars in corresponding constraints
    std::vector<size_t> basic(cons);
    for (auto &i: basic) {
        std::cin >> i;
    }

    // Input the approximation accuracy
    double accuracy;
    std::cin >> accuracy;

    std::cout << "-------------------------------------------------------------------------------------------\n";
    Simplex<Fraction> simplex(obj, coeffs_frac, A_frac, b_frac, basic);
    Solution<Fraction> simplex_solution = simplex.find_solution();
    std::cout << simplex_solution;
    if (!simplex_solution.is_final() || simplex_solution.is_unbounded()) return EXIT_FAILURE;
    std::cout << "-------------------------------------------------------------------------------------------\n";
    try {
        InteriorPoint<double> interiorPoint_half(obj, coeffs_double, A_double, b_double, accuracy, 0.5,
                                                 basic);
        std::vector<double> solution_1 = interiorPoint_half.solve();
        interiorPoint_half.form_answer();
    } catch (MatrixException &e) {
        std::cout << "Interior point for alpha = 0.5 cannot be solved due to singularity of"
                     " one of the iteration matrices\n";
    }
    std::cout << "-------------------------------------------------------------------------------------------\n";
    try {
        InteriorPoint<double> interiorPoint_approx(obj, coeffs_double, A_double, b_double, accuracy, 0.9,
                                                   basic);
        std::vector<double> solution_2 = interiorPoint_approx.solve();
        interiorPoint_approx.form_answer();
    } catch (MatrixException &e) {
        std::cout << "Interior point for alpha = 0.9 cannot be solved due to singularity of"
                     " one of the iteration matrices\n";
    }
    std::cout << "-------------------------------------------------------------------------------------------\n";

    return EXIT_SUCCESS;
}
