// prob1140: Stone Game II

/*
 * https://leetcode-cn.com/problems/stone-game-ii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        sums = vector<int>(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + piles[i - 1];
        dp = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(2, vector<int>(n * 2, -1)));
        return solve(piles, 0, 0, 1);
    }

private:
    vector<vector<vector<int>>> dp;
    vector<int> sums;

    int solve(const vector<int>& piles, int i, int round, int M)
    {
        if(dp[i][round][M] != -1)
            return dp[i][round][M];

        int n = piles.size();
        if(i == n)
            return dp[i][round][M] = 0;

        int remain = n - i;
        if(round == 0)
            dp[i][round][M] = 0;
        else
            dp[i][round][M] = sums[n];
        for(int m = 1; m <= min(remain, M * 2); ++m)
        {
            int sum = sums[i + m] - sums[i];
            if(round == 0)
                dp[i][round][M] = max(dp[i][round][M], sum + solve(piles, i + m, round ^ 1, max(M, m)));
            else
                dp[i][round][M] = min(dp[i][round][M], solve(piles, i + m, round ^ 1, max(M, m)));
        }
        return dp[i][round][M];
    }
};
