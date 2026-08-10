#include "../include/graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

CSRGraph loadCSRGraph(const std::string& filename)
{
    std::ifstream infile(filename);
    CSRGraph graph;
    if(!infile.is_open())
    {
        std::cerr<<"Error: Cannot open file: "<<filename<<std::endl;
        return graph;
    }
    std::string line;
    int V = 0;
    int E = 0;
    //to parse header line having V and E
    while(std::getline(infile, line))
    {
        if(line.empty()||line[0]=='#')
            continue;
        std::stringstream ss(line);
        if(ss>>V>>E)
        {
            break;
        }
    }

    if(V <= 0)
    {
        infile.close();
        return graph;
    }
    graph.num_vertices = V;
    graph.num_edges = E;
    std::vector<std::vector<int>>adj_neighbors(V);

    while(std::getline(infile, line))
    {
        if(line.empty()||line[0]=='#')
            continue;
        std::stringstream ss(line);
        std::string first_token;
        ss >> first_token;
        //check for SOURCE tag
        if(first_token=="SOURCE"||first_token=="source"||first_token=="Source")
        {
            ss>>graph.source_vertex;
            continue;
        }
        int u;
        try
        {
            u=std::stoi(first_token);
        }
        catch (...)
        {
            continue;//to skip invalid tokens
        }

        if(u<0||u>=V)
            continue;
        int degree;
        if (!(ss>>degree))
            continue;
        for(int i=0;i<degree;++i)
        {
            int v;
            if(!(ss>>v))
                break;

            if(v>=0&&v<V)
            {
                adj_neighbors[u].push_back(v);
            }
        }
    }
    infile.close();

    graph.row_ptr.resize(V+1, 0);

    for (int i=0;i<V;++i)
    {
        graph.row_ptr[i+1]=graph.row_ptr[i] + static_cast<int>(adj_neighbors[i].size());
    }
    int total_edges = graph.row_ptr[V];
    graph.col_ind.reserve(total_edges);
    for (int i = 0; i < V; ++i)
    {
        for (size_t j = 0; j < adj_neighbors[i].size(); ++j)
        {
            graph.col_ind.push_back(adj_neighbors[i][j]);
        }
    }
    graph.num_edges = total_edges;
    return graph;
}

