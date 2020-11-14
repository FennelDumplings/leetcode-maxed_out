// prob1411: Number of Ways to Paint N × 3 Grid

/*
 * https://leetcode-cn.com/problems/number-of-ways-to-paint-n-x-3-grid/
 */

#include <vector>

using namespace std;

// 自动机 D

// dp[v][i] := 考虑 [0..i] 行且当前的第 i 行在状态 v 的方案数
// sum(dp[v][n - 1])
// dp[v][0] = 1
// dp[v][i] = dp[u][i - 1]  其中 D[u][v] == 1

class Solution {
public:
    int numOfWays(int n) {
        for(int i = 1; i <= 3; ++i)
        {
            int state = (1 << (i - 1));
            dfs(state, i, 1);
        }
        int N = node.size();
        D = vector<vector<int>>(N, vector<int>(N));
        for(int i = 0; i < N - 1; ++i)
            for(int j = i + 1; j < N; ++j)
                if(check(i, j))
                    D[i][j] = D[j][i] = 1;
        vector<vector<int>> dp(N, vector<int>(n));
        for(int u = 0; u < N; ++u)
            dp[u][0] = 1;
        for(int i = 1; i < n; ++i)
            for(int u = 0; u < N; ++u)
                for(int v = 0; v < N; ++v)
                    if(D[u][v] == 1)
                        dp[u][i] = (dp[u][i] + (ll)dp[v][i - 1]) % MOD;
        int ans = 0;
        for(int u = 0; u < N; ++u)
            ans = (ans + (ll)dp[u][n - 1]) % MOD;
        return ans;
    }

private:
    vector<int> node; // node[i] := 节点 i 代表的一行颜色状态为 node[i]
    vector<vector<int>> D;
    using ll = long long;
    const int MOD = 1e9 + 7;

    bool check(int i, int j)
    {
        return (node[i] & node[j]) == 0;
    }

    void dfs(int state, int prev, int len)
    {
        if(len == 3)
        {
            node.push_back(state);
            return;
        }
        for(int j = 1; j <= 3; ++j)
        {
            if(j == prev) continue;
            int nxt = state;
            nxt <<= 3;
            nxt |= (1 << (j - 1));
            dfs(nxt, j, len + 1);
        }
    }
};
