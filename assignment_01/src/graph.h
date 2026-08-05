#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>


//graph structure
struct CSRGraph {
    int num_vertices = 0;
    int num_edges = 0;
    std:: vector<int> row_ptr;
    std ::  vector<int> col_ind;
    std:: vector<double> weights;// weighted graph
};

//returning csr
CSRGraph loadCSRGraph(const std::string& filename);

#endif // GRAPH_H