#include<iostream>
#include<chrono>
#include<string>
#include<fstream>
#include "../src/graph.h"
using namespace std;
using namespace std::chrono;
ofstream fout;

//dfs function declaration
void dfs(CSRGraph &g,int src);

int main(int argc, char* argv[])
{
    if(argc < 2)
{
    cerr << "Usage: " << argv[0]
         << " <graph_file> [source_node]" << endl;
    return 1;
}

string file = argv[1];
int src = (argc >= 3) ? stoi(argv[2]) : 0;

CSRGraph g = loadCSRGraph(file);
    fout.open("outputs/dfs_output.txt");
    fout << "Algorithm: DFS" << endl;
    fout << "Source: " << src << endl;
    fout << "Traversal: ";
    //start time 
    auto start = high_resolution_clock::now();
    //calling dfs function
    dfs(g,src);
    //stop time
    auto stop = high_resolution_clock::now();
    //calculate exceution time
    auto t = duration_cast<microseconds>(stop - start);
    //display exceution time
    double time = t.count() / 1000.0;   // Convert microseconds to milliseconds

    cout << "Execution time : "<<time<<" ms"<<endl;

    fout << endl;
    fout << "Execution time : "<<time<<" ms"<< endl;
    fout.close();
    return 0;
}

