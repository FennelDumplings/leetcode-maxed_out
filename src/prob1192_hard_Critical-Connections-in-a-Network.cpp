// prob1192: Critical Connections in a Network

/*
 * https://leetcode-cn.com/problems/critical-connections-in-a-network/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> g(n);
        for(const vector<int>& edge: connections)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        vector<int> ord(n, n);
        vector<int> low(n, n);
        vector<vector<int>> result;
        dfs(g, 0, -1, visited, ord, low, 0, result);
        return result;
    }

private:
    void dfs(const vector<vector<int>>& g, int node, int prev, vector<bool>& visited, vector<int>& ord,
            vector<int>& low, int total, vector<vector<int>>& result)
    {
        if(visited[node])
            return;
        visited[node] = true;
        ord[node] = total;
        low[node] = total;
        int min_low = total;
        for(int son: g[node])
        {
            // (node, son) 这条边
            if(son == prev)
                continue;
            dfs(g, son, node, visited, ord, low, total + 1, result);
            if(low[son] > ord[node])
                result.push_back({node, son});
            min_low = min(min_low, low[son]);
        }
        low[node] = min_low;
    }
};
