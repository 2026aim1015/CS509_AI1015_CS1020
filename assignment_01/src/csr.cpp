#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "graph.h"

using namespace std;

//implementation to convert graph files
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
    
    //for storing llist and weights
    vector<vector<int>> adj(num_v);
    vector<vector<double>> weight_adj(num_v);

    string line;
    getline(infile, line);

    // graph read line by line 
    while (getline(infile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        int u, v;
        double w = 1.0; // Default weight for unweighted edges
        if (ss >> u >> v) {
            // Read weights if available
            if (!(ss >> w)) {
                w = 1.0;
            }
            if (u >= 0 && u < num_v && v >= 0 && v < num_v) {
                adj[u].push_back(v);
                weight_adj[u].push_back(w);
            }
        }
    }
    infile.close();
    // csr arrays 
    graph.row_ptr.resize(num_v + 1, 0);

    for (int i = 0; i < num_v; ++i) {
        graph.row_ptr[i + 1] = graph.row_ptr[i] + adj[i].size();
        for (size_t j = 0; j < adj[i].size(); ++j) {
            graph.col_ind.push_back(adj[i][j]);
            graph.weights.push_back(weight_adj[i][j]);
        }
    }

    graph.num_edges = static_cast<int>(graph.col_ind.size());

    return graph;
}