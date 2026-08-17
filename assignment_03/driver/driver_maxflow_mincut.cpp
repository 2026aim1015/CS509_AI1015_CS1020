#include "../include/graph.h"
#include "../include/maxflow_mincut.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <tuple>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        cout << "Usage: " << argv[0]
             << " <input_file> [output_file]" << endl;

        return 1;
    }

    string filename = argv[1];

    ifstream test_file(filename);

    if(!test_file.is_open())
    {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    test_file.close();

    CSRGraph graph = loadCSRGraph(filename);

    if (graph.num_vertices <= 0)
    {
        cerr << "Error: Invalid graph." << endl;
        return 1;
    }

    ifstream file(filename);

    if(!file.is_open())
    {
        cerr << "Error: Could not reopen input file." << endl;
        return 1;
    }

    int V, E;
    file >> V >> E;

    //skip adjacency-list information
    for (int u = 0; u < V; u++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        for (int j = 0; j < degree; j++)
        {
            int neighbor;
            double capacity;

            file >> neighbor >> capacity;
        }
    }

    string source_label;
    string sink_label;

    int source;
    int sink;

    file >> source_label >> source;
    file >> sink_label >> sink;

    file.close();

    if (source < 0 || source >= V)
    {
        cerr << "Error: Invalid source vertex." << endl;
        return 1;
    }

    if (sink < 0 || sink >= V)
    {
        cerr << "Error: Invalid sink vertex." << endl;
        return 1;
    }

    if (source == sink)
    {
        cerr << "Error: Source and sink must be different." << endl;
        return 1;
    }

    auto start_time =
        chrono::high_resolution_clock::now();

    MaxFlowResult result =
        maxFlowMinCut(graph, source, sink);

    auto end_time =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed =
        end_time - start_time;

    if (argc == 3)
    {
        ofstream output(argv[2]);

        if (!output.is_open())
        {
            cerr << "Error: Could not create output file." << endl;
            return 1;
        }

        output << "Algorithm: Maxflow-Mincut" << endl;
        output << "Source: " << source << endl;
        output << "Sink: " << sink << endl;

        output << "Maximum flow: "
               << fixed << setprecision(0)
               << result.max_flow << endl;

        output << "Minimum cut capacity: "
               << fixed << setprecision(0)
               << result.min_cut_capacity << endl;

        output << "Source side: ";

        for (int v : result.source_side)
        {
            output << v << " ";
        }

        output << endl;

        output << "Sink side: ";

        for (int v : result.sink_side)
        {
            output << v << " ";
        }

        output << endl;

        output << "Cut edges:" << endl;

        for (const auto& edge : result.cut_edges)
        {
            output << get<0>(edge) << " "
                   << get<1>(edge) << " "
                   << fixed << setprecision(0)
                   << get<2>(edge)
                   << endl;
        }

        output << "Execution time: "
               << fixed << setprecision(6)
               << elapsed.count()
               << " ms" << endl;

        output.close();

        cout << "Output saved to: " << argv[2] << endl;
    }
    else
    {
        cout << "Algorithm: Maxflow-Mincut" << endl;
        cout << "Source: " << source << endl;
        cout << "Sink: " << sink << endl;

        cout << "Maximum flow: "
             << fixed << setprecision(0)
             << result.max_flow << endl;

        cout << "Minimum cut capacity: "
             << fixed << setprecision(0)
             << result.min_cut_capacity << endl;

        cout << "Source side: ";

        for (int v : result.source_side)
        {
            cout << v << " ";
        }

        cout << endl;

        cout << "Sink side: ";

        for (int v : result.sink_side)
        {
            cout << v << " ";
        }

        cout << endl;

        cout << "Cut edges:" << endl;

        for (const auto& edge : result.cut_edges)
        {
            cout << get<0>(edge) << " "
                 << get<1>(edge) << " "
                 << fixed << setprecision(0)
                 << get<2>(edge)
                 << endl;
        }

        cout << "Execution time: "
             << fixed << setprecision(6)
             << elapsed.count()
             << " ms" << endl;
    }

    return 0;
}