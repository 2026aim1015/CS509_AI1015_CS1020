#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "sssp_csr.h"

using namespace std;

WeightedCSRGraph loadWeightedCSRGraph(const string& filename)
{
    ifstream infile(filename);
    WeightedCSRGraph graph;
    cout << "Loading file: " << filename << endl;
    if (!infile.is_open())
    {
        cerr << "Error: Cannot open graph file " << filename << endl;
        return graph;
    }

    int num_v = 0, num_e = 0;
    infile >> num_v >> num_e;

    graph.num_vertices = num_v;

    vector<vector<int>> adj(num_v);
    vector<vector<int>> weight_adj(num_v);

    string line;

    getline(infile, line);

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string first_token;
        ss >> first_token;

        if (first_token == "SOURCE")
            continue;

        int u = stoi(first_token);

        int degree;
        ss >> degree;

        for (int i = 0; i < degree; i++)
        {
            int v;
            int w;

            ss >> v >> w;

            if (u >= 0 && u < num_v && v >= 0 && v < num_v)
            {
                adj[u].push_back(v);
                weight_adj[u].push_back(w);
            }
        }
    }

    infile.close();

    graph.row_ptr.resize(num_v + 1, 0);

    for (int i = 0; i < num_v; i++)
    {
        graph.row_ptr[i + 1] =
            graph.row_ptr[i] + adj[i].size();

        for (size_t j = 0; j < adj[i].size(); j++)
        {
            graph.col_ind.push_back(adj[i][j]);
            graph.weights.push_back(weight_adj[i][j]);
        }
    }

    graph.num_edges = graph.col_ind.size();

    return graph;
}