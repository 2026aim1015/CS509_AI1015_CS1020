#ifndef BETWEENNESS_CENTRALITY_HPP
#define BETWEENNNESS_CENTRALITY_HPP

#include "graph.h"
#include <vector>

struct BCResult{
    std::vector<double> centrality;
};

BCResult runBetweennessCentrality(const CSRGraph& graph);

#endif