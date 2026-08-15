#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
struct CSRGraph
{
    int num_vertices = 0;
    int num_edges = 0;
    std::vector<int> row_ptr;
    std::vector<int> col_ind;
    std::vector<double> weights;
};

CSRGraph loadCSRGraph(const std::string& filename);

#endif