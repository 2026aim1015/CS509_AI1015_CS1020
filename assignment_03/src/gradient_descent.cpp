#include "../include/gradient_descent.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>

// Evaluates f(x) = c0 + c1*x + c2*x^2 + ... + cd*x^d using Horner's Method
double evaluatePolynomial(const std::vector<double>& coeffs, double x) {
    if (coeffs.empty()) return 0.0;
    
    // Horner's evaluation for numerical stability
    double result = coeffs.back();
    for (int i = static_cast<int>(coeffs.size()) - 2; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

// Evaluates derivative f'(x) = c1 + 2*c2*x + 3*c3*x^2 + ...
double evaluateDerivative(const std::vector<double>& coeffs, double x) {
    if (coeffs.size() <= 1) return 0.0; // Derivative of constant/empty polynomial is 0

    // Build derivative coefficients
    std::vector<double> derivCoeffs;
    for (size_t i = 1; i < coeffs.size(); ++i) {
        derivCoeffs.push_back(static_cast<double>(i) * coeffs[i]);
    }

    // Evaluate using Horner's rule
    double result = derivCoeffs.back();
    for (int i = static_cast<int>(derivCoeffs.size()) - 2; i >= 0; --i) {
        result = result * x + derivCoeffs[i];
    }
    return result;
}

// Core optimization loop handling convergence and safety boundaries
GDResult runGradientDescent(const GDInput& input) {
    GDResult res;
    double current_x = input.x0;
    res.iterations_taken = 0;
    res.converged = false;

    // Edge Case: Invalid or non-positive parameters guard
    if (input.learning_rate <= 0.0 || input.tolerance <= 0.0 || input.coeffs.empty()) {
        res.optimal_x = current_x;
        res.optimal_fx = evaluatePolynomial(input.coeffs, current_x);
        return res;
    }

    for (int iter = 0; iter < input.max_iterations; ++iter) {
        double grad = evaluateDerivative(input.coeffs, current_x);
        res.iterations_taken++;

        // Edge Case 1: Gradient becomes NaN or Inf (divergence/overshoot)
        if (std::isnan(grad) || std::isinf(grad) || std::isnan(current_x) || std::isinf(current_x)) {
            res.converged = false;
            break;
        }

        // Edge Case 2: Stationary point or flat gradient reached (|f'(x)| < tolerance)
        if (std::abs(grad) < input.tolerance) {
            res.converged = true;
            break;
        }

        double next_x = current_x - input.learning_rate * grad;

        // Edge Case 3: Step movement is smaller than tolerance (|x_{k+1} - x_k| < tolerance)
        if (std::abs(next_x - current_x) < input.tolerance) {
            current_x = next_x;
            res.converged = true;
            break;
        }

        current_x = next_x;
    }

    res.optimal_x = current_x;
    res.optimal_fx = evaluatePolynomial(input.coeffs, current_x);
    return res;
}

// Untimed file parsing
GDInput loadGDInput(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open test file: " + filepath);
    }

    GDInput input;

    // Line 1: Degree
    if (!(file >> input.degree) || input.degree < 0) {
        throw std::runtime_error("Invalid or missing polynomial degree in " + filepath);
    }

    // Line 2: Coefficients c0, c1, ..., cd
    input.coeffs.resize(input.degree + 1);
    for (int i = 0; i <= input.degree; ++i) {
        if (!(file >> input.coeffs[i])) {
            throw std::runtime_error("Incomplete coefficient entries in " + filepath);
        }
    }

    // Line 3: x0, learning_rate (eta), tolerance (epsilon)
    if (!(file >> input.x0 >> input.learning_rate >> input.tolerance)) {
        throw std::runtime_error("Missing parameter line (x0, eta, tolerance) in " + filepath);
    }

    file.close();
    return input;
}