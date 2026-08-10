#include "graph.h"
#include "betweenness_centrality.hpp"
#include "timer.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    if(argc < 2){
        cerr << "Usage :" << argv[0] << "<input_file_path> [output_file_path]\n";
        return 1;
    }

    string  input_filename = argv[1];
    string output_filename = (argc >= 3) ? argv[2] : "";


    CSRGraph graph = loadCSRGraph(input_filename);
    if(graph.num_vertices == 0){
        cerr << "error failed to load graph\n";
        return 1;
    }

    Timer timer;
    timer.start();
    BCResult res = runBetweennessCentrality(graph);
    timer.stop();

    double elapsed_ms = timer.elapsedMs();

    if(elapsed_ms < 5.0){
        int runs = 100;
        timer.start();
        for(int r = 0; r< runs ; ++r){
            res = runBetweennessCentrality(graph);
        }

        timer.stop();
        elapsed_ms = timer.elapsedMs()/runs;
    }

    cout << "ALGO : Betweenness Centrality\n";
    cout << "Vertex Centrality\n";
    std::cout << std::fixed << std::setprecision(2);
    for(int i =0; i < graph.num_vertices; ++i){
        cout << i << " " << res.centrality[i] << "\n";
    } 

    std:: cout << std::setprecision(4);
    std:: cout << "execution time :" << elapsed_ms << "ms\n";

    if (!output_filename.empty()){
        ofstream outfile(output_filename);
        if(outfile.is_open()){
            outfile << "algo : betweenness centrality \n";
            outfile << "vertex centrality\n";
            outfile << std::fixed << std:: setprecision(2);
            for(int i =0; i< graph.num_vertices; ++i){
                outfile << i << " "  << res.centrality[i] << "\n";
            }

            outfile << std::setprecision(4);
            outfile << "execution time: " << elapsed_ms << "ms\n";
            outfile.close();
            std:: cout << "\nresults saved to :" << output_filename << "\n";
        }
    }
    return 0;
}

