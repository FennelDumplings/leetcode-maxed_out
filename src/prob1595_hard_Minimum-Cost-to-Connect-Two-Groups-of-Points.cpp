// prob1595: Minimum Cost to Connect Two Groups of Points

/*
 * https://leetcode-cn.com/problems/minimum-cost-to-connect-two-groups-of-points/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        int n = cost.size(), m = cost[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(1 << m, INT_MAX / 2));
        dp[0][0] = 0;
        for(int i = 1; i <= n; ++i)
        {
            for(int state = 0; state < (1 << m); ++state)
            {
                for(int j = 0; j < m; ++j)
                {
                    if((state >> j & 1) == 0)
                    {
                        dp[i][state | (1 << j)] = min(dp[i][state | (1 << j)], dp[i - 1][state] + cost[i - 1][j]);
                        dp[i][state | (1 << j)] = min(dp[i][state | (1 << j)], dp[i][state] + cost[i - 1][j]);
                    }
                    else
                    {
                        dp[i][state] = min(dp[i][state], dp[i - 1][state] + cost[i - 1][j]);
                    }
                }
            }
        }
        return dp[n][(1 << m) - 1];
    }
};
