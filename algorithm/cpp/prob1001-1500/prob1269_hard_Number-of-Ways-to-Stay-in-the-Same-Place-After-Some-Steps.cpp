// prob1269: Number of Ways to Stay in the Same Place After Some Steps

/*
 * https://leetcode-cn.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numWays(int steps, int arrLen) {
        n = min(steps + 1, arrLen);
        dp = vector<vector<int>>(n + 1, vector<int>(steps + 1, -1));
        return solve(0, steps);
    }

private:
    vector<vector<int>> dp;
    using ll = long long;
    const int MOD = 1e9 + 7;
    int n;

    int solve(int i, int k)
    {
        if(i > k) return 0;
        if(dp[i][k] != -1)
            return dp[i][k];
        if(i == 0 && k == 0)
            return dp[i][k] = 1;
        dp[i][k] = 0;
        dp[i][k] = ((ll)dp[i][k] + solve(i, k - 1)) % MOD;
        if(i > 0)
            dp[i][k] = ((ll)dp[i][k] + solve(i - 1, k - 1)) % MOD;
        if(i < n - 1)
            dp[i][k] = ((ll)dp[i][k] + solve(i + 1, k - 1)) % MOD;
        return dp[i][k];
    }
};
