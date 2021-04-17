// prob799: Champagne Tower

/*
 * https://leetcode-cn.com/problems/champagne-tower/
 */

/*
dp[i][j] := 第 i 行第 j 个杯子的量

dp[0][0] = S

转移
dp[i][1] = 1/2 * (dp[i - 1][1] - 1)
dp[i][i] = 1/2 * (dp[i - 1][i - 1] - 1)
dp[i][j] = 1/2 * (dp[i - 1][j] - 1) + 1/2 * (dp[i - 1][j - 1] - 1)
*/

#include <vector>

using namespace std;

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        int S = poured;
        int n = query_row, m = query_glass;
        vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0));
        dp[0][0] = S;
        for(int i = 1; i <= n; ++i)
        {
            dp[i][0] = 0.5 * (max(dp[i - 1][0] - 1, 0.0));
            dp[i][i] = 0.5 * (max(dp[i - 1][i - 1] - 1, 0.0));
            for(int j = 1; j < i; ++j)
                dp[i][j] = 0.5 * (max(dp[i - 1][j] - 1, 0.0)) + 0.5 * (max(dp[i - 1][j - 1] - 1, 0.0));
        }
        return min(dp[n][m], 1.0);
    }
};
