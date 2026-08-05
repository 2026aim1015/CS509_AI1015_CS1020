#ifndef SSSP_CSR_H
#define SSSP_CSR_H

#include <vector>
#include <string>

using namespace std;

struct WeightedCSRGraph
{
    int num_vertices;
    int num_edges;

    vector<int> row_ptr;
    vector<int> col_ind;
    vector<int> weights;
};

WeightedCSRGraph loadWeightedCSRGraph(const string& filename);

#endif