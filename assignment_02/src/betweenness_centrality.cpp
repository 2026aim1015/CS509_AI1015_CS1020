#include "../include/betweenness_centrality.hpp"
#include <queue>
#include <stack>
#include <vector>
using namespace std;

BCResult runBetweennessCentrality(const CSRGraph& graph){
    BCResult result;
    int V = graph.num_vertices;
    if (V <=0 ) return result;

    result.centrality.assign(V, 0.0);

    for(int s = 0; s < V ; ++s ){
        stack<int> S;
        vector<vector<int>> P(V);
        vector<long long> sigma(V,0);
        vector<int> d(V, -1);

        sigma[s] = 1;
        d[s] = 0;

        queue<int> Q;
        Q.push(s);



        while(!Q.empty()){
            int v = Q.front();
            Q.pop();
            S.push(v);

            int start_idx = graph.row_ptr[v];
            int end_idx = graph.row_ptr[v+1];

            for(int idx = start_idx; idx < end_idx; ++idx){
                int w = graph.col_ind[idx];

                if(d[w] < 0){
                    Q.push(w);
                    d[w] = d[v] + 1;
                }

                if (d[w] == d[v]+1){
                    sigma[w] += sigma[v];
                    P[w].push_back(v);
                }
            }
        }

        vector<double> delta(V, 0.0);
        while(!S.empty()){
            int w = S.top();
            S.pop();

            for(int  v : P[w]){
                if(sigma[w] > 0){
                    delta[v] += (static_cast<double>(sigma[v]) / sigma[w]) * (1.0 +delta[w]);
                }
            }

            if(w != s){
                result.centrality[w] += delta[w];
            }
        }

    }

    for(int i = 0; i < V ; ++i){
        result.centrality[i] /= 2.0;
    }

    return result;
}