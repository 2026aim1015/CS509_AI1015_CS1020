<<<<<<< HEAD
#include<iostream>
#include <vector>
#include <queue>
#include "graph.h"

void runBFS(const CSRGraph& graph, int source,vector<int>)
=======
#include <iostream>
#include <chrono>
#include <string>
#include "../src/graph.h"
using namespace std;
using namespace std::chrono;

//dfs function declaration
void dfs(CSRGraph &g,int src);

int main()
{
    string file;
    //take input file
    cout<<"Enter file name : ";
    cin>>file;
    //load graph into csr format
    CSRGraph g = loadCSRGraph(file);
    //check whether graph is loaded successfully 
    if (g.num_vertices == 0)
    {
        cout<<"Graph loading failed."<<endl;
        return 0;
    }

    int src;
    //read the source vertex
    cout<<"Enter source vertex : ";
    cin>>src;
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

    cout << "Execution time : "
        << time
        << " ms" << endl;

    return 0;
}
>>>>>>> 3507c79105c3329c334410d661b2465207d31982
