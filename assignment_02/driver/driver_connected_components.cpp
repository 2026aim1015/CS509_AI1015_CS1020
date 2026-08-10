#include "../include/graph.h"
#include "../include/connected_components.h"
#include<iostream>
#include<fstream>
#include<chrono>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr<<"Usage: "<<argv[0]<<" <input_file>"<<std::endl;
        return 1;
    }
    //input file 
    std::string file = argv[1];
    std::ifstream infile(file);
    if(!infile.is_open())
    {
        std::cerr<<"Error: Could not open input file: "<< file<< std::endl;
        return 1;
    }
    infile.close();
    //calling csr function ,graph to csr
    CSRGraph graph = loadCSRGraph(file);
    if(graph.num_vertices<=0)
    {
        std::cerr<<"Error: Invalid graph."<<std::endl;
        return 1;
    }

    std::cout<<"Graph loaded successfully."<<std::endl;
    std::cout<<"Vertices: "<<graph.num_vertices<<std::endl;
    std::cout<<"Edges: "<<graph.num_edges<<std::endl;
    std::cout << std::endl;
    // allocate component array that store connected component vertice
    int* com_id =new int[graph.num_vertices];
    auto start =std::chrono::high_resolution_clock::now();
    // calling connected component algorithm
    int total_com =connectedComponents(graph, com_id);
    auto end =std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli>execution_time = end - start;

    std::cout<<"Algorithm: Connected Components"<<std::endl;
    std::cout<<"Number of components: "<<total_com<<std::endl;
    std::cout<<"Component IDs:"<<std::endl;
    //give the vertice with its component id
    for(int v = 0;v < graph.num_vertices;++v)
    {
        std::cout<<"Vertex "<<v<< ": Component "<<com_id[v]<< std::endl;
    }

    std::cout<<"Execution time: "<<execution_time.count()<<" ms"<<std::endl;
    delete[] com_id;

    return 0;
}

