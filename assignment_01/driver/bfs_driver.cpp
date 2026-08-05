#include <iostream>
#include <vector>
#include <chrono>
#include "../src/graph.h"
using namespace std;
#include <fstream>

ofstream fout;
// runBFS from bfs.cpp
void runBFS(const CSRGraph& graph,int source,vector<int>& distances,vector<int>& parent,vector<int>& traversal);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file> [source_node]" << endl;
        return 1;
    }
    vector<int> traversal;
    string graph_file = argv[1];
    int source = (argc >= 3) ? std::stoi(argv[2]) : 0;

    CSRGraph graph = loadCSRGraph(graph_file);

    if (graph.num_vertices == 0)
    {
        cerr << "Graph loading failed." << endl;
        return 1;
    }

    cout << "Running BFS on graph (" << graph.num_vertices << " vertices, "
        << graph.num_edges << " edges) from source " << source << "...\n";

    vector<int> distances; //distances vector
    vector<int> parent;    //parent vector
    fout.open("outputs/bfs_output.txt");
    //clock usuage
    auto start_time = chrono::high_resolution_clock::now();
    runBFS(graph, source, distances, parent, traversal);
    auto end_time = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, milli>(end_time - start_time).count();

    int visited_count = 0;
    for (int d : distances) {
        if (d != -1) visited_count++;
    }
    cout << "Algorithm: BFS" << endl;
    cout << "Source: " << source << endl;

    fout << "Algorithm: BFS" << endl;
    fout << "Source: " << source << endl;

    cout << "Traversal: ";
    fout << "Traversal: ";

    for (int v : traversal)
    {
        cout << v << " ";
        fout << v << " ";
    }

    cout << endl;
    fout << endl;

    cout << "Distances:" << endl;
    fout << "Distances:" << endl;

    for (int i = 0; i < graph.num_vertices; i++)
    {
        cout << i << " " << distances[i] << endl;
        fout << i << " " << distances[i] << endl;
    }

    cout << "Execution time: "
        << elapsed_ms
        << " ms" << endl;

    fout << "Execution time: "
        << elapsed_ms
        << " ms" << endl;
    fout.close();
        return 0;
}