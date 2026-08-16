#include "gradient_descent.h"
#include "timer.hpp"
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <test_file_path>\n";
        return 1;
    }

    std::string filepath = argv[1];
    GDInput input;

    try {
        // Untimed preprocessing
        input = loadGDInput(filepath);

        Timer timer;
        timer.start();
        GDResult result = runGradientDescent(input);
        timer.stop();

        // Exact formatting matching Section 6.3
        std::cout << "Algorithm: Gradient Descent\n";
        std::cout << "Degree: " << input.degree << "\n";
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Final x: approximately " << result.optimal_x << "\n";
        std::cout << "Final f(x): approximately " << result.optimal_fx << "\n";
        std::cout << "Iterations: " << result.iterations_taken << "\n";
        std::cout << "Converged: " << (result.converged ? "true" : "false") << "\n";
        std::cout << std::setprecision(4);
        std::cout << "Execution time: " << timer.elapsedMs() << " ms\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}