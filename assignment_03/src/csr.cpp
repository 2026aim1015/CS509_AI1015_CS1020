#include "../include/graph.h"
#include <fstream>
#include <iostream>

CSRGraph loadCSRGraph(const std::string& filename)
{
    CSRGraph graph;
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr<<"Error: Could not open input file: "<<filename<<std::endl;
        return graph;
    }
    int V, E;
    //take no of vertices and edge from graph
    file>>V>>E;
    graph.num_vertices = V;
    graph.num_edges = E;
    //size of row_ptr taken according to number of vertices
    graph.row_ptr.resize(V + 1, 0);

    std::vector<std::vector<int>> neigh(V);
    std::vector<std::vector<double>> cap(V);

    for(int u = 0; u < V; u++)
    {
        int degree;
        file >> degree;
        for(int j=0;j<degree;j++)
        {
            int v;
            double capacity;
            file >> v >> capacity;
            neigh[u].push_back(v);
            cap[u].push_back(capacity);
        }
    }
    //csr row_ptr tell where u start in col_ind and weights
    for (int u = 0; u < V; u++)
    {
        graph.row_ptr[u + 1] = graph.row_ptr[u] + neigh[u].size();
    }
    int t_edges = graph.row_ptr[V];
    if (t_edges!= E)
    {
        std::cerr<<"Warning: Edge count does not match input."<<std::endl;
    }
    graph.col_ind.resize(t_edges);
    graph.weights.resize(t_edges);
    //fill col_ind and weights
    int index = 0;
    for(int u = 0; u < V; u++)
    {
        for(int j=0;j<neigh[u].size(); j++)
        {
            graph.col_ind[index] = neigh[u][j];
            graph.weights[index] = cap[u][j];
            index++;
        }
    }
    file.close();
    return graph;
}