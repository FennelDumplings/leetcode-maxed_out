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

        vector<int> dfn(n);
        vector<int> low(n);
        vector<vector<int>> result;
        int dfnid = 0;
        dfs(g, 0, -1, dfn, low, dfnid, result);
        return result;
    }

private:
    void dfs(const vector<vector<int>>& g, int node, int prev, vector<int>& dfn,
            vector<int>& low, int& dfnid, vector<vector<int>>& result)
    {
        if(dfn[node] != 0)
            return;
        dfn[node] = ++dfnid;
        low[node] = dfnid;
        int min_low = dfnid;
        int cnt = 0;
        for(int son: g[node])
        {
            // (node, son) 这条边
            if(son == prev)
            {
                if(++cnt > 1)
                    min_low = min(min_low, dfn[son]);
                continue;
            }
            dfs(g, son, node, dfn, low, dfnid, result);
            if(low[son] > dfn[node])
                result.push_back({node, son});
            min_low = min(min_low, low[son]);
        }
        low[node] = min_low;
    }
};
