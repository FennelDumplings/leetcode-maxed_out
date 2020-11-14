// prob1563: Stone Game V

/*
 * https://leetcode-cn.com/problems/stone-game-v/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        dp = vector<vector<int>>(n, vector<int>(n, -1));
        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + stoneValue[i - 1];
        for(int i = 0; i < n; ++i)
        {
            dp[i][i] = 0;
        }
        return solve(0, n - 1, sums);
        return dp[0][n - 1];
    }

private:
    vector<vector<int>> dp;

    int solve(int i, int j, const vector<int>& sums)
    {
        if(dp[i][j] != -1)
            return dp[i][j];

        dp[i][j] = 0;
        for(int k = i; k < j; ++k)
        {
            int sum_l = sums[k + 1] - sums[i];
            int sum_r = sums[j + 1] - sums[k + 1];
            if(sum_l > sum_r)
            {
                dp[i][j] = max(solve(k + 1, j, sums) + sum_r, dp[i][j]);
            }
            else if(sum_l < sum_r)
            {
                dp[i][j] = max(solve(i, k, sums) + sum_l, dp[i][j]);
            }
            else
            {
                dp[i][j] = max(max(solve(i, k, sums), solve(k + 1, j, sums)) + sum_l, dp[i][j]);
            }
        }
        return dp[i][j];
    }
};
