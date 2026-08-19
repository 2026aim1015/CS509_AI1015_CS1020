#ifndef MAXFLOW_MINCUT_H
#define MAXFLOW_MINCUT_H
#include "graph.h"
#include <vector>

//edge in residual graph
struct FlowEdge
{
    int to;
    int rev;
    double capacity;
};

//to store result of maxflow-mincut
struct MaxFlowResult
{
    double max_flow;
    double min_cut_capacity;

    std::vector<int> source_side;
    std::vector<int> sink_side;

    //cut edge have source , destination and capacity
    std::vector<std::tuple<int, int, double>> cut_edges;
};

// dinic's algorithm
MaxFlowResult maxFlowMinCut(
    const CSRGraph& graph,
    int source,
    int sink
);

#endif