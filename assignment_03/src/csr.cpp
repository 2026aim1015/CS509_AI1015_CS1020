#include "../include/graph.h"

#include <fstream>
#include <iostream>

CSRGraph loadCSRGraph(const std::string& filename)
{
    CSRGraph graph;

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open input file."
                  << std::endl;

        return graph;
    }

    int V;
    int E;

    file >> V >> E;

    graph.num_vertices = V;
    graph.num_edges = E;

    graph.row_ptr.resize(V + 1, 0);

    for (int u = 0; u < V; u++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        graph.row_ptr[vertex + 1] =
            graph.row_ptr[vertex] + degree;
    }

    file.clear();
    file.seekg(0);

    file >> V >> E;

    std::vector<int> degrees(V);

    for (int u = 0; u < V; u++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        degrees[vertex] = degree;

        for (int j = 0; j < degree; j++)
        {
            int neighbor;
            double capacity;

            file >> neighbor >> capacity;
        }
    }

    graph.row_ptr[0] = 0;

    for (int u = 0; u < V; u++)
    {
        graph.row_ptr[u + 1] =
            graph.row_ptr[u] + degrees[u];
    }

    int total_edges = graph.row_ptr[V];

    if (total_edges != E)
    {
        std::cerr << "Warning: Edge count does not match input."
                  << std::endl;
    }

    graph.col_ind.resize(total_edges);
    graph.weights.resize(total_edges);

    file.clear();
    file.seekg(0);

    file >> V >> E;

    for (int u = 0; u < V; u++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        int start = graph.row_ptr[vertex];

        for (int j = 0; j < degree; j++)
        {
            int neighbor;
            double capacity;

            file >> neighbor >> capacity;

            graph.col_ind[start + j] = neighbor;
            graph.weights[start + j] = capacity;
        }
    }

    file.close();

    return graph;
}