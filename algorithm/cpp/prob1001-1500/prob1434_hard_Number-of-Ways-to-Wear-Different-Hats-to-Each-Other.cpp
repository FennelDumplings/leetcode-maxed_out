// prob1434: Number of Ways to Wear Different Hats to Each Other

/*
 * https://leetcode-cn.com/problems/number-of-ways-to-wear-different-hats-to-each-other/
 */

#include <vector>

using namespace std;


// dp[i][state] := [0..i] 上有 state 这些人选帽子的方案数
// dp[m][(1 << n) - 1] 为答案
// 初始化　dp[0][0] = 1
// 转移
// dp[i][s] += dp[i - 1][s]
// dp[i][s | (1 << j)] += dp[i - 1][s]   其中 rg[i] 中有 j 且 (s & (1 << j)) == 0

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        const int MOD = 1e9 + 7;
        using ll = long long;
        const int m = 40;
        vector<vector<int>> rg(m + 1);
        int n = hats.size();
        for(int j = 0; j < n; ++j)
            for(int i: hats[j])
                rg[i].push_back(j);
        vector<vector<int>> dp(m + 1, vector<int>(1 << n));
        dp[0][0] = 1;
        for(int state = 0; state < (1 << n); ++state)
            for(int i = 1; i <= m; ++i)
            {
                dp[i][state] = (dp[i][state] + (ll)dp[i - 1][state]) % MOD;
                for(int j: rg[i])
                {
                    if(state >> j & 1) continue;
                    dp[i][state | (1 << j)] = (dp[i][state | (1 << j)] + (ll)dp[i - 1][state]) % MOD;
                }
            }
        return dp[m][(1 << n) - 1];
    }
};
