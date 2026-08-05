#include <iostream>
#include <vector>
#include <chrono>
#include "../src/graph.h"
using namespace std;

// runBFS from bfs.cpp
void runBFS(const CSRGraph& graph, int source,vector<int>& distances,vector<int>& parent);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file> [source_node]" << endl;
        return 1;
    }

    string graph_file = argv[1];
    int source = (argc >= 3) ? std::stoi(argv[2]) : 0;

    CSRGraph graph = loadCSRGraph(graph_file);

    cout << "Running BFS on graph (" << graph.num_vertices << " vertices, " 
              << graph.num_edges << " edges) from source " << source << "...\n";

    vector<int> distances; //distances vector
    vector<int> parent;    //parent vector

    //clock usuage
    auto start_time = chrono::high_resolution_clock::now();
    runBFS(graph, source, distances, parent);
    auto end_time = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, milli>(end_time - start_time).count();

    int visited_count = 0;
    for (int d : distances) {
        if (d != -1) visited_count++;
    }
     //execution time
    cout << "BFS completed in " << elapsed_ms << " ms.\n";
    cout << "Visited Vertices: " << visited_count << " / " << graph.num_vertices << "\n";

    return 0;
}