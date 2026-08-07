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

