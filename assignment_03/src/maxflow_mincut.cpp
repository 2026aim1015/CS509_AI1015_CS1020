#include "../include/maxflow_mincut.h"
#include <queue>
#include <tuple>
#include <algorithm>

//add an edge to residual graph
static void addEdge(std::vector<std::vector<FlowEdge>>& residual,int u,int v,double capacity)
{
    FlowEdge forward;
    forward.to = v;
    forward.rev = residual[v].size();
    forward.capacity = capacity;

    FlowEdge reverse;
    reverse.to = u;
    reverse.rev = residual[u].size();
    reverse.capacity = 0.0;

    residual[u].push_back(forward);
    residual[v].push_back(reverse);
}


//BFS creates level graph
static bool bfs(const std::vector<std::vector<FlowEdge>>& residual,int source,int sink,std::vector<int>& level)
{
    int n = residual.size();
    level.assign(n, -1);
    std::queue<int> q;
    level[source] = 0;
    q.push(source);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(const FlowEdge& edge : residual[u])
        {
            if(edge.capacity > 0 && level[edge.to] == -1)
            {
                level[edge.to] = level[u] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[sink] != -1;
}
//DFS sends blocking flow through the level graph
static double dfs(std::vector<std::vector<FlowEdge>>& residual,std::vector<int>& level,std::vector<int>& next_edge,int u,int sink,double flow)
{
    if(u == sink)
    {
        return flow;
    }
    for(int& i = next_edge[u];i < static_cast<int>(residual[u].size());i++)
    {
        FlowEdge& edge = residual[u][i];
        if (edge.capacity > 0&&level[edge.to] == level[u] + 1)
        {
            double possible_flow =std::min(flow, edge.capacity);
            double pushed = dfs(residual,level,next_edge,edge.to,sink,possible_flow);
            if(pushed>0)
            {
                edge.capacity -= pushed;
                residual[edge.to][edge.rev].capacity += pushed;
                return pushed;
            }
        }
    }
    return 0.0;
}

MaxFlowResult maxFlowMinCut(const CSRGraph& graph,int source,int sink)
{
    MaxFlowResult result;
    result.max_flow = 0.0;
    result.min_cut_capacity = 0.0;

    int n = graph.num_vertices;

    //Build residual graph from CSR
    std::vector<std::vector<FlowEdge>> residual(n);
    for(int u = 0; u < n; u++)
    {
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u+1];
        for(int i = start; i < end; i++)
        {
            int v = graph.col_ind[i];
            double capacity = graph.weights[i];
            addEdge(residual,u,v,capacity);
        }
    }

    // Dinic's algorithm
    std::vector<int> level(n);
    std::vector<int> next_edge(n);
    while(bfs(residual, source, sink, level))
    {
        std::fill(next_edge.begin(),next_edge.end(),0);
        while(true)
        {
            double pushed = dfs(residual,level,next_edge,source,sink,1e100);
            if(pushed<=0)
            {
                break;
            }
            result.max_flow += pushed;
        }
    }

    //find vertices reachable from source
    std::vector<bool> reachable(n, false);
    std::queue<int> q;
    reachable[source] = true;
    q.push(source);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (const FlowEdge& edge : residual[u])
        {
            if (edge.capacity>0 && !reachable[edge.to])
            {
                reachable[edge.to] = true;
                q.push(edge.to);
            }
        }
    }

    // divide vertices into source side and sink side
    for(int v=0;v<n;v++)
    {
        if(reachable[v])
        {
            result.source_side.push_back(v);
        }
        else
        {
            result.sink_side.push_back(v);
        }
    }

    //find original edges crossing the cut
    for(int u=0;u<n;u++)
    {
        if(!reachable[u])
        {
            continue;
        }
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];
        for(int i=start;i<end;i++)
        {
            int v = graph.col_ind[i];
            double capacity = graph.weights[i];
            if (!reachable[v])
            {
                result.cut_edges.emplace_back(u,v,capacity);
                result.min_cut_capacity += capacity;
            }
        }
    }
    return result;
}