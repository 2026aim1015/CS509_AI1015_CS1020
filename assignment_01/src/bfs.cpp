#include<iostream>
#include <vector>
#include <queue>
#include "graph.h"
using namespace std;


//run bfs function taking infut in csr 
void runBFS(const CSRGraph& graph, int source,vector<int>& distances, vector<int>& parent){
    int num_vertices = graph.num_vertices;

    distances.assign(num_vertices, -1);
    parent.assign(num_vertices, -1);

    if(source < 0 || source >= num_vertices){
        cerr<<"error invalid source vertex";
        return;
    }

    queue<int>q;

    distances[source]=0;
    q.push(source);

    while(!q.empty()){
        int u =q.front();
        q.pop();

        int start_edge = graph.row_ptr[u];
        int end_edge = graph.row_ptr[u+1];

        for (int e = start_edge; e< end_edge; ++e){
            int v= graph.col_ind[e];

            if(distances[v] == -1){
                distances[v] = distances[u]+1;
                parent[v]=u;
                q.push(v);
            }
        }
    }
}