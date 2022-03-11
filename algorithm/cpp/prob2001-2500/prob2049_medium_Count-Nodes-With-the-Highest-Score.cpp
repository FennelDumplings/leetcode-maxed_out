#include <vector>

using namespace std;

class Solution {
public:
    int countHighestScoreNodes(vector<int>& parents) {
        int n = parents.size();
        vector<vector<int>> g(n);
        int root = -1;
        for(int u = 0; u < n; ++u)
        {
            int fa = parents[u];
            if(fa == -1)
            {
                root = u;
                continue;
            }
            g[fa].push_back(u);
        }
        vector<int> dp(n, -1);
        dfs(g, dp, root);
        long long max_score = 0;
        int max_cnt = 0;
        for(int u = 0; u < n; ++u)
        {
            long long score = 1;
            for(int v: g[u])
                score *= dp[v];
            if(root != u)
                score *= (dp[root] - dp[u]);
            if(score > max_score)
            {
                max_score = score;
                max_cnt = 1;
            }
            else if(score == max_score)
                max_cnt += 1;
        }
        return max_cnt;
    }

    int dfs(const vector<vector<int>>& g, vector<int>& dp, int u)
    {
        if(dp[u] != -1)
            return dp[u];
        dp[u] = 1;
        for(int v: g[u])
            dp[u] += dfs(g, dp, v);
        return dp[u];
    }
};
