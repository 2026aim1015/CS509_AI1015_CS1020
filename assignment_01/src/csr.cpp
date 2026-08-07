#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "graph.h"

using namespace std;

CSRGraph loadCSRGraph(const string& filename) {
    ifstream infile(filename);
    CSRGraph graph;

    if (!infile.is_open()) {
        cerr << "Error: Cannot open graph file " << filename << endl;
        return graph;
    }

    int num_v = 0, num_e = 0;
    infile >> num_v >> num_e;

    graph.num_vertices = num_v;

    vector<vector<int>> adj(num_v);
    vector<vector<double>> weight_adj(num_v);

    string line;
    // Consume remaining newline character after reading graph size
    getline(infile, line);

    while (getline(infile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string first_token;

        if(!(ss >> first_token)) continue;

        // Stop or skip if we encounter the SOURCE specifier at the end
        if (first_token == "SOURCE") continue;

        int u = stoi(first_token);
        int degree = 0;
        
        if (ss >> degree) {
            for (int i = 0; i < degree; ++i) {
                int v;
                if (ss >> v) {
                    if (u >= 0 && u < num_v && v >= 0 && v < num_v) {
                        adj[u].push_back(v);
                        weight_adj[u].push_back(1.0); // Default unweighted edge cost
                    }
                }
            }
        }
    }
    infile.close();

    // Build CSR structure
    graph.row_ptr.resize(num_v + 1, 0);

    for (int i = 0; i < num_v; ++i) {
        graph.row_ptr[i + 1] = graph.row_ptr[i] + static_cast<int>(adj[i].size());

        for (size_t j = 0; j < adj[i].size(); ++j) {
            graph.col_ind.push_back(adj[i][j]);
            graph.weights.push_back(weight_adj[i][j]);
        }
    }

    graph.num_edges = static_cast<int>(graph.col_ind.size());

    return graph;
}