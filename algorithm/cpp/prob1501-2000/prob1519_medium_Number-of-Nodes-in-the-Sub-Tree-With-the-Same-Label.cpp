// prob1519: Number of Nodes in the Sub-Tree With the Same Label

/*
 * https://leetcode-cn.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        // dp[u][ch] := 子树 u 上标签 ch 的个数
        dp = vector<vector<int>>(n);

        vector<vector<int>> g(n);
        for(const vector<int> &e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<bool> visited(n, false);
        visited[0] = true;
        dfs(g, 0, visited, labels);
        vector<int> result(n);
        for(int i = 0; i < n; ++i)
            result[i] = dp[i][labels[i] - 'a'];
        return result;
    }


private:
    vector<vector<int>> dp;

    void dfs(const vector<vector<int>>& g, int u, vector<bool>& visited, const string& labels)
    {
        if(!dp[u].empty())
            return;

        dp[u] = vector<int>(26);
        dp[u][labels[u] - 'a'] = 1;
        for(int v: g[u])
        {
            if(visited[v]) continue;
            visited[v] = true;
            dfs(g, v, visited, labels);
            for(char ch = 'a'; ch <= 'z'; ++ch)
                dp[u][ch - 'a'] += dp[v][ch - 'a'];
        }
    }
};
