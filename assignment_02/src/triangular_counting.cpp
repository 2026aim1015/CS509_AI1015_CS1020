#include "../include/triangular_counting.h"
#include <vector>

bool hasEdge(const CSRGraph& graph, int u, int v)
{
    for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i)
    {
        if (graph.col_ind[i] == v)
        {
            return true;
        }
    }

    return false;
}

long long countTriangles(const CSRGraph& graph)
{
    long long triangle_count = 0;

    int V = graph.num_vertices;

    for (int u = 0; u < V; ++u)
    {
        
        for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i)
        {
            int v = graph.col_ind[i];

            
            if (v <= u)
                continue;

            for (int j = graph.row_ptr[u]; j < graph.row_ptr[u + 1]; ++j)
            {
                int w = graph.col_ind[j];

               
                if (w <= v)
                    continue;

                if (hasEdge(graph, v, w))
                {
                    triangle_count++;
                }
            }
        }
    }

    return triangle_count;
}