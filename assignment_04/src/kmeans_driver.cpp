#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include "kmeans.hpp"
#include "timer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_points_file>\n";
        return 1;
    }

    std::string filepath = argv[1];
    std::ifstream infile(filepath);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open input file: " << filepath << "\n";
        return 1;
    }

    KMeansParams params;
    std::vector<std::vector<double>> points;

    try {
        std::string line;
        // Read header line: N D K
        while (std::getline(infile, line)) {
            if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
            std::stringstream ss(line);
            if (ss >> params.N >> params.D >> params.K) break;
        }

        // Section 12 Validation: Reject non-positive parameters or K > N
        if (params.N <= 0 || params.D <= 0 || params.K <= 0 || params.K > params.N) {
            throw std::runtime_error("Invalid N, D, or K values (N, D, K > 0 and K <= N required).");
        }

        points.reserve(params.N);

        // Read point coordinates and configuration keywords
        while (std::getline(infile, line)) {
            if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
            std::stringstream ss(line);
            std::string first_token;
            ss >> first_token;

            if (first_token == "MAX_ITERATIONS") {
                ss >> params.max_iterations;
                if (params.max_iterations <= 0) {
                    throw std::runtime_error("Invalid MAX_ITERATIONS <= 0");
                }
            } else if (first_token == "TOLERANCE") {
                ss >> params.tolerance;
                if (params.tolerance <= 0.0) {
                    throw std::runtime_error("Invalid TOLERANCE <= 0.0");
                }
            } else {
                std::vector<double> pt(params.D);
                pt[0] = std::stod(first_token);
                for (int d = 1; d < params.D; ++d) {
                    if (!(ss >> pt[d])) {
                        throw std::runtime_error("Malformed point coordinate row.");
                    }
                }
                points.push_back(pt);
            }
        }
        infile.close();

        if (static_cast<int>(points.size()) != params.N) {
            throw std::runtime_error("Input point count does not match declared N.");
        }

    } catch (const std::exception& e) {
        std::cerr << "Input Error: " << e.what() << "\n";
        return 1;
    }

    // Timed Section: Algorithm Execution Only
    Timer timer;
    timer.start();
    KMeansResult result = runKMeans(points, params);
    timer.stop();

    // Section 7.3 Expected Output Format
    std::cout << "Algorithm: K-Means Clustering\n";
    std::cout << "K: " << params.K << "\n";
    std::cout << "Point assignments:\n";
    for (int i = 0; i < params.N; ++i) {
        std::cout << i << " " << result.assignments[i] << "\n";
    }
    std::cout << "Final centroids:\n";
    std::cout << std::fixed << std::setprecision(6);
    for (int k = 0; k < params.K; ++k) {
        std::cout << k << ":";
        for (int d = 0; d < params.D; ++d) {
            std::cout << " " << result.centroids[k][d];
        }
        std::cout << "\n";
    }
    std::cout << "WCSS: " << result.wcss << "\n";
    std::cout << "Iterations: " << result.iterations << "\n";
    std::cout << "Converged: " << (result.converged ? "true" : "false") << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << timer.elapsedMs() << " ms\n";

    return 0;
}