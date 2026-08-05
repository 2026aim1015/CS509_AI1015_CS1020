#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <climits>

#include "../src/sssp_csr.h"

using namespace std;
using namespace chrono;

ofstream fout;

// Function declaration
void dijkstra(const WeightedCSRGraph &graph,
              int source,
              vector<int> &dist,
              vector<int> &parent);

int main()
{
    string filename;

    cout << "Enter graph file : ";
    cin >> filename;

    WeightedCSRGraph graph = loadWeightedCSRGraph(filename);

    if(graph.num_vertices == 0)
    {
        cout << "Graph loading failed." << endl;
        return 0;
    }

    int source;

    cout << "Enter source vertex : ";
    cin >> source;

    if(source < 0 || source >= graph.num_vertices)
    {
        cout << "Invalid source vertex." << endl;
        return 0;
    }

    fout.open("outputs/sssp_output.txt");

    vector<int> dist;
    vector<int> parent;

    auto start = high_resolution_clock::now();

    dijkstra(graph, source, dist, parent);

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