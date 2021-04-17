// prob688: Knight Probability in Chessboard

/*
 * https://leetcode-cn.com/problems/knight-probability-in-chessboard/
 */

#include <vector>

using namespace std;


class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        // 1 <= 1 <= 25
        int n = N, m = N;
        vector<vector<vector<double>>> dp(n, vector<vector<double>>(m, vector<double>(K + 1, -1.0)));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                dp[i][j][0] = 1.0;
        return solve(r, c, K, n, m, dp);
    }

private:
    int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};

    double solve(int i, int j, int k, const int n, const int m, vector<vector<vector<double>>>& dp)
    {
        if(dp[i][j][k] > -0.5)
            return dp[i][j][k];

        dp[i][j][k] = 0.0;
        for(int d = 0; d < 8; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            dp[i][j][k] += 0.125 * (solve(x, y, k - 1, n, m, dp));
        }
        return dp[i][j][k];
    }
};
