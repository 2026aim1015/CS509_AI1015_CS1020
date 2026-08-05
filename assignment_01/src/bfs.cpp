#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"

using namespace std;

void runBFS(const CSRGraph& graph, int source, vector<int>& distances, vector<int>& parent, vector<int>& visit_order) {
    int num_vertices = graph.num_vertices;

    distances.assign(num_vertices, -1);
    parent.assign(num_vertices, -1);
    visit_order.clear();

    if (source < 0 || source >= num_vertices) {
        cerr << "Error: Invalid source vertex " << source << endl;
        return;
    }

    queue<int> q;

    distances[source] = 0;
    q.push(source);
    visit_order.push_back(source); // Track starting node

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int start_edge = graph.row_ptr[u];
        int end_edge = graph.row_ptr[u + 1];

        for (int e = start_edge; e < end_edge; ++e) {
            int v = graph.col_ind[e];

            if (distances[v] == -1) {
                distances[v] = distances[u] + 1;
                parent[v] = u;
                q.push(v);
                visit_order.push_back(v); // Record node in order of discovery
            }
        }
    }
}