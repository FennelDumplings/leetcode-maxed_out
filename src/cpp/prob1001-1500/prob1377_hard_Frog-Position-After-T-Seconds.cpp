// prob1377: Frog Position After T Seconds

/*
 * Given an undirected tree consisting of n vertices numbered from 1 to n. A frog starts jumping from the vertex 1.
 * In one second, the frog jumps from its current vertex to another unvisited vertex if they are directly connected.
 * The frog can not jump back to a visited vertex. In case the frog can jump to several vertices it jumps randomly to
 * one of them with the same probability, otherwise, when the frog can not jump to any unvisited vertex it jumps forever on the same vertex. 
 * The edges of the undirected tree are given in the array edges, where edges[i] = [fromi, toi] means that exists an edge
 * connecting directly the vertices fromi and toi.
 * Return the probability that after t seconds the frog is on the vertex target.
 */

/*
 * Constraints:
 * 1 <= n <= 100
 * edges.length == n-1
 * edges[i].length == 2
 * 1 <= edges[i][0], edges[i][1] <= n
 * 1 <= t <= 50
 * 1 <= target <= n
 * Answers within 10^-5 of the actual value will be accepted as correct.
 */

#include <vector>

using namespace std;

class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        if(n == 1) return 1.0;
        vector<vector<int> > g(n + 1);
        vector<int> fa(n + 1, -1);
        for(const vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        int start = 1, end = target;
        vector<int> path(1, start);
        dfs(g, path, start, end, -1);

        int len = path.size();
        if(t > len - 1 && !_is_leaf(g, target)) return 0.0;
        if(t < len - 1) return 0.0;
        double result = 1.0;
        for(int i = 0; i < len; ++i)
        {
            if(_is_leaf(g, path[i])) break;
            int k = g[path[i]].size() - 1;
            if(path[i] == 1) k += 1;
            result /= k;
        }
        return result;
    }

private:
    bool _is_leaf(vector<vector<int> >& g, int cur)
    {
        if(cur == 1) return false;
        return g[cur].size() == 1;
    }

    bool dfs(vector<vector<int> >& g, vector<int>& path, int cur, int end, int fa)
    {
        if(cur == end) return true;
        for(int son: g[cur])
        {
            if(son == fa) continue;
            path.push_back(son);
            if(dfs(g, path, son, end, cur))
                return true;
            path.pop_back();
        }
        return false;
    }
};
