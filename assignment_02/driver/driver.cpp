#include "..\include\graph.h"
#include "..\include\triangle_counting.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: "
                  << argv[0]
                  << " <input_file>"
                  << std::endl;

        return 1;
    }

    std::string filename = argv[1];

    // Check input file
    std::ifstream infile(filename);

    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open input file: "
                  << filename << std::endl;

        return 1;
    }

    infile.close();

    // -----------------------------------------
    // Load and convert graph to CSR
    // NOT included in algorithm timing
    // -----------------------------------------
    CSRGraph graph = loadCSRGraph(filename);

    if (graph.num_vertices <= 0)
    {
        std::cerr << "Error: Invalid graph."
                  << std::endl;

        return 1;
    }
    
    std::cout << std::endl;
    std::cout << "Algorithm: Triangle Counting"
              << std::endl;

    // -----------------------------------------
    // Triangle Counting
    // -----------------------------------------
    auto start = std::chrono::high_resolution_clock::now();

    long long total_triangles = countTriangles(graph);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli>
        execution_time = end - start;


    std::cout << "Total triangles: "
              << total_triangles
              << std::endl;

    // Triangles were already printed by
    // countTriangles()

    std::cout << "Execution time: "
              << execution_time.count()
              << " ms"
              << std::endl;

    return 0;
}

