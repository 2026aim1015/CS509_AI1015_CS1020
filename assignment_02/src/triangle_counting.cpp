#include "../include/triangle_counting.h"
#include<iostream>
//to check an edge between u and v
bool hasEdge(const CSRGraph& graph, int u, int v)
{
    for(int i = graph.row_ptr[u];i < graph.row_ptr[u + 1];++i)
    {
        if(graph.col_ind[i] == v)
        {
            return true;
        }
    }
    return false;
}
//counting triangle
long long countTriangles(const CSRGraph& graph)
{
    long long triangle_count = 0;
    int V = graph.num_vertices;
    std::cout << "Triangles found:" << std::endl;

    for (int u = 0; u < V; ++u)
    {
        //neighbours of u
        for(int i = graph.row_ptr[u];i < graph.row_ptr[u + 1];++i)
        {
            int v = graph.col_ind[i];
            //maintain u<v
            if (v <= u)
                continue;
            // check for other neighbours of u
            for (int j = graph.row_ptr[u];j < graph.row_ptr[u + 1];++j)
            {
                int w = graph.col_ind[j];
                //maintain u<v<w
                if (w <= v)
                    continue;
                //check is there a edge between v and w
                if (hasEdge(graph, v, w))
                {
                    triangle_count++;
                    std::cout<<"("<< u <<","<<v<<", "<<w<<")"<<std::endl;
                }
            }
        }
    }
    return triangle_count;
}
