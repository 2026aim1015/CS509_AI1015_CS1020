#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>
#include <string>

// Input container holding polynomial data and parameters
struct GDInput {
    int degree;                     // Degree d (e.g., 2 to 10)
    std::vector<double> coeffs;     // Coefficients [c0, c1, ..., cd]
    double x0;                      // Starting initial point
    double learning_rate;           // Learning rate / step size (eta)
    double tolerance;               // Stopping tolerance (epsilon)
    int max_iterations = 1000000;   // Safety iteration limit
};

// Result container
struct GDResult {
    double optimal_x;
    double optimal_fx;
    int iterations_taken;
    bool converged;
};

// Core function declarations
double evaluatePolynomial(const std::vector<double>& coeffs, double x);
double evaluateDerivative(const std::vector<double>& coeffs, double x);
GDResult runGradientDescent(const GDInput& input);
GDInput loadGDInput(const std::string& filepath);

#endif // GRADIENT_DESCENT_H