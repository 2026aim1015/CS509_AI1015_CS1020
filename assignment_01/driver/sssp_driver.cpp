#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <climits>

#include "../src/sssp_csr.h"

using namespace std;
using namespace chrono;

ofstream fout;

// Function predeclaration
void dijkstra(const WeightedCSRGraph &graph,
              int source,
              vector<int> &dist,
              vector<int> &parent);

int main(int argc, char* argv[])
{
    if(argc < 2)
{
    cerr << "Usage: " << argv[0]
         << " <graph_file> [source_node]" << endl;
    return 1;
}

string filename = argv[1];
int source = (argc >= 3) ? stoi(argv[2]) : 0;

WeightedCSRGraph graph = loadWeightedCSRGraph(filename);

    if(source < 0 || source >= graph.num_vertices)
    {
        cout << "Invalid source vertex." << endl;
        return 0;
    }

    fout.open("outputs/sssp_output.txt");

    vector<int> dist;
    vector<int> parent;
   // clock start 
    auto start = high_resolution_clock::now();
    //dijkstra
    dijkstra(graph, source, dist, parent);
   // clock end
    auto stop = high_resolution_clock::now();

    double time =
        duration_cast<microseconds>(stop-start).count()/1000.0;

    // Console Output
    cout << "Algorithm: SSSP" << endl;
    cout << "Source: " << source << endl;
    cout << endl;

    cout << "Vertex\tDistance" << endl;

    // File Output
    fout << "Algorithm: SSSP" << endl;
    fout << "Source: " << source << endl;
    fout << endl;

    fout << "Vertex\tDistance" << endl;

    for(int i=0;i<graph.num_vertices;i++)
    {
        cout << i << "\t";
        fout << i << "\t";

        if(dist[i]==INT_MAX)
        {
            cout << "INF" << endl;
            fout << "INF" << endl;
        }
        else
        {
            cout << dist[i] << endl;
            fout << dist[i] << endl;
        }
    }

    cout << endl;
    cout << "Execution time: "
         << time
         << " ms" << endl;

    fout << endl;
    fout << "Execution time: "
         << time
         << " ms" << endl;

    fout.close();

    return 0;
}