// prob1059: All Paths from Source Lead to Destination

/*
 * https://leetcode-cn.com/problems/all-paths-from-source-lead-to-destination/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> g(n);
        for(vector<int> &e: edges)
            g[e[0]].push_back(e[1]);
        vector<int> visited(n, 0);
        visited[source] = 1;
        return dfs(g, source, destination, visited);
    }

private:
    bool dfs(const vector<vector<int>>& g, int u, const int t, vector<int>& visited)
    {
        if(g[u].empty())
        {
            visited[u] = 2;
            return u == t;
        }
        for(int v: g[u])
        {
            if(visited[v] == 1)
                return false;
            if(visited[v] == 2)
                continue;
            visited[v] = 1;
            if(!dfs(g, v, t, visited))
                return false;
        }
        visited[u] = 2;
        return true;
    }
};
