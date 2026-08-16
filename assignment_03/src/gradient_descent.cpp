#include "gradient_descent.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

// Horner's evaluation for numerical stability on polynomials up to degree 10
double evaluatePolynomial(const std::vector<double>& coeffs, double x) {
    if (coeffs.empty()) return 0.0;
    
    double val = coeffs.back();
    for (int i = static_cast<int>(coeffs.size()) - 2; i >= 0; --i) {
        val = val * x + coeffs[i];
    }
    return val;
}

// Derivative computation: f'(x) = c1 + 2*c2*x + 3*c3*x^2 + ...
double evaluateDerivative(const std::vector<double>& coeffs, double x) {
    if (coeffs.size() <= 1) return 0.0;

    std::vector<double> derivCoeffs;
    derivCoeffs.reserve(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        derivCoeffs.push_back(static_cast<double>(i) * coeffs[i]);
    }

    double val = derivCoeffs.back();
    for (int i = static_cast<int>(derivCoeffs.size()) - 2; i >= 0; --i) {
        val = val * x + derivCoeffs[i];
    }
    return val;
}

// Optimization loop: x_new = x - alpha * f'(x)
GDResult runGradientDescent(const GDInput& input) {
    GDResult res;
    double current_x = input.x0;
    res.iterations_taken = 0;
    res.converged = false;

    for (int iter = 0; iter < input.max_iterations; ++iter) {
        double grad = evaluateDerivative(input.coeffs, current_x);
        res.iterations_taken++;

        // Divergence guard
        if (std::isnan(grad) || std::isinf(grad) || std::isnan(current_x) || std::isinf(current_x)) {
            res.converged = false;
            break;
        }

        // Stopping condition: |f'(x)| <= epsilon
        if (std::abs(grad) <= input.tolerance) {
            res.converged = true;
            break;
        }

        // Gradient Descent update step
        current_x = current_x - input.learning_rate * grad;
    }

    // Final convergence check in case loop exhausted
    if (!res.converged) {
        double final_grad = evaluateDerivative(input.coeffs, current_x);
        if (std::abs(final_grad) <= input.tolerance) {
            res.converged = true;
        }
    }

    res.optimal_x = current_x;
    res.optimal_fx = evaluatePolynomial(input.coeffs, current_x);
    return res;
}

// Keyword-based input parser adhering strictly to Section 6.1
GDInput loadGDInput(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }

    GDInput input;
    std::string tag;

    while (file >> tag) {
        if (tag == "DEGREE") {
            file >> input.degree;
        } else if (tag == "COEFFICIENTS") {
            input.coeffs.resize(input.degree + 1);
            for (int i = 0; i <= input.degree; ++i) {
                file >> input.coeffs[i];
            }
        } else if (tag == "INITIAL_X") {
            file >> input.x0;
        } else if (tag == "LEARNING_RATE") {
            file >> input.learning_rate;
        } else if (tag == "TOLERANCE") {
            file >> input.tolerance;
        } else if (tag == "MAX_ITERATIONS") {
            file >> input.max_iterations;
        }
    }

    file.close();
    return input;
}