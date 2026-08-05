#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;
// recursive dfs function
void dfsUtil(int v, CSRGraph &g, vector<bool> &vis)
{
    //mark current vertex is visited
    vis[v] = true;

    cout <<v<<" ";
    //traverse all neighbours of current vertex
    for (int i= g.row_ptr[v]; i<g.row_ptr[v + 1];i++)
    {
        int u = g.col_ind[i];
        //visit only if neighbour is not visited
        if (vis[u]==false)
        {
            dfsUtil(u,g,vis);
        }
    }
}

// DFS function
void dfs(CSRGraph &g,int src)
{
    //array to keep track of visited node
    vector<bool>vis(g.num_vertices,false);

    cout << "Algorithm : DFS" << endl;
    cout << "Source : " << src << endl;
    cout << "Traversal : ";

    dfsUtil(src, g, vis);

    cout << endl;
}