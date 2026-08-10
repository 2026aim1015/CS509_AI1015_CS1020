#include "../include/connected_components.h"

int connectedComponents(const CSRGraph& graph, int* com_id)
{
    int V= graph.num_vertices;
    //take all vertices as unvisited
    for(int i = 0;i<V;++i)
    {
        com_id[i] = -1;
    }
    int com_count = 0;
    for(int j= 0; j< V; ++j)
    {
        if(com_id[j] != -1)
        {
            continue;
        }
        //queue for bfs
        int* queue = new int[V];
        //here f is front of queue and r is rear of queue
        int f = 0;
        int r = 0;
        com_id[j] = com_count;
        queue[r++] = j;
        //bfs
        while (f<r)
        {
            int u = queue[f++];
            //traverse all neighbours of u
            for(int i = graph.row_ptr[u];i < graph.row_ptr[u + 1];++i)
            {
                int v = graph.col_ind[i];
                //if vertice v is been not visited
                if(com_id[v] == -1)
                {
                    com_id[v] = com_count;
                    queue[r++] = v;
                }
            }
        }
        delete[] queue;
        //move to next component
        com_count++;
    }
    return com_count;
}

