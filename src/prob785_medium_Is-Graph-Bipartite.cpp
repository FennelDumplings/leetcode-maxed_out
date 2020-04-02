// prob785: Is Graph Bipartite

/*
 * Given an undirected graph, return true if and only if it is bipartite.
 * Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B
 * such that every edge in the graph has one node in A and another node in B.
 * The graph is given in the following form: graph[i] is a list of indexes j for which the edge
 * between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.
 * There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        if(graph.empty()) return false;
        int n = graph.size();
        if(n == 1) return true;

        int st;
        queue<int> q;
        vector<int> d(n, 0);

        for(int i = 0; i < n; ++i)
        {
            if(d[i] == 0)
                st = i;
            q.push(st);
            d[st] = 1;
            while(!q.empty())
            {
                int u = q.front(); // 当前点
                q.pop();
                for(int v: graph[u])
                {
                    if(d[v] != 0)
                    {
                        if(!(d[u] ^ d[v]))
                            return false;
                        else
                            continue;
                    }
                    d[v] = -d[u];
                    q.push(v);
                }
            }
        }
        return true;
    }
};
