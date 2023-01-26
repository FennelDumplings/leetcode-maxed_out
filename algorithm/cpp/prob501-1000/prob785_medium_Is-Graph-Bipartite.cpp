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

class UnionFindSet {
public:
    UnionFindSet(int n)
    {
        _father = vector<int>(n, -1);
        _rank = vector<int>(n, 0);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
    }

    ~UnionFindSet(){}

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y) return;

        // 此时 x, y 是所在树的根
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

private:
    vector<int> _father;
    vector<int> _rank;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        else
            return _father[x] = _find(_father[x]); // 路径压缩
    }
};

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        UnionFindSet unionfindset(n);
        for(int u = 0; u < n; ++u)
        {
            if(graph[u].empty())
                continue;
            int m = graph[u].size();
            int v0 = graph[u][0];
            for(int i = 1; i < m; ++i)
            {
                int v = graph[u][i];
                if(unionfindset.same(u, v))
                    return false;
                unionfindset.merge(v0, v);
            }
        }
        return true;
    }
};

class Solution_2 {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        if(graph.empty()) return false;
        int n = graph.size();
        if(n == 1) return true;

        int st;
        vector<int> d(n, 0);

        for(int i = 0; i < n; ++i)
        {
            if(d[i] != 0) continue;
            st = i;
            d[st] = 1;
            // if(!bfs(graph, st, d))
            if(!dfs(graph, st, d))
                return false;
        }
        return true;
    }

private:
    bool bfs(const vector<vector<int>>& g, int st, vector<int>& d)
    {
        queue<int> q;
        q.push(st);
        while(!q.empty())
        {
            int u = q.front(); // 当前点
            q.pop();
            for(int v: g[u])
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
        return true;
    }

    bool dfs(const vector<vector<int>>& g, int u, vector<int>& d)
    {
        for(int v: g[u])
        {
            if(d[v] != 0)
            {
                if(!(d[v] ^ d[u]))
                    return false;
                continue;
            }
            d[v] = -d[u];
            if(!dfs(g, v, d))
                return false;
        }
        return true;
    }
};
