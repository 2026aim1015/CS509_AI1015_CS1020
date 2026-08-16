#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>
#include <string>

// Input container holding polynomial data and parameters
struct GDInput {
    int degree = 0;
    std::vector<double> coeffs;     // Ascending order: c0, c1, ..., cd
    double x0 = 0.0;
    double learning_rate = 0.01;
    double tolerance = 1e-6;
    int max_iterations = 10000;
};

// Result container
struct GDResult {
    double optimal_x = 0.0;
    double optimal_fx = 0.0;
    int iterations_taken = 0;
    bool converged = false;
};

// Function declarations
double evaluatePolynomial(const std::vector<double>& coeffs, double x);
double evaluateDerivative(const std::vector<double>& coeffs, double x);
GDResult runGradientDescent(const GDInput& input);
GDInput loadGDInput(const std::string& filepath);

#endif // GRADIENT_DESCENT_H