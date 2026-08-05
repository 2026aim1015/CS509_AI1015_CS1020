#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include "sssp_csr.h"

using namespace std;

// Output file declared in driver
extern ofstream fout;

// Dijkstra's Algorithm
void dijkstra(const WeightedCSRGraph &graph,
              int source,
              vector<int> &dist,
              vector<int> &parent)
{
    int V = graph.num_vertices;

    dist.assign(V, INT_MAX);
    parent.assign(V, -1);

    // (distance, vertex)
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while(!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(d > dist[u])
            continue;

        for(int i = graph.row_ptr[u];
            i < graph.row_ptr[u+1];
            i++)
        {
            int v = graph.col_ind[i];
            int w = graph.weights[i];

            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;

                pq.push({dist[v], v});
            }
        }
    }
}