// prob983: Minimum Cost For Tickets

/*
 * https://leetcode-cn.com/problems/minimum-cost-for-tickets/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        vector<vector<int>> dp(n, vector<int>(4, INT_MAX));
        dp[0][1] = costs[0], dp[0][2] = costs[1], dp[0][3] = costs[2];
        for(int i = 1; i < n; ++i)
        {
            int minx = dp[i - 1][0];
            for(int k = 1; k < 4; ++k)
                minx = min(minx, dp[i - 1][k]);
            dp[i][1] = minx + costs[0];
            dp[i][2] = minx + costs[1];
            dp[i][3] = minx + costs[2];
            if(days[i] >= days[i - 1] + 30) // dp[i][0] = INF
                continue;
            // days[i] < days[i - 1] + 30
            // dp[i][0] 可能被前面的 30 覆盖
            for(int j = i - 1; j >= 0 && days[j] + 30 > days[i]; --j)
                dp[i][0] = min(dp[i][0], dp[j][3]);
            // dp[i][0] 可能还有可能被前面的 7 覆盖
            for(int j = i - 1; j >= 0 && days[j] + 7 > days[i]; --j)
                dp[i][0] = min(dp[i][0], dp[j][2]);
        }
        int ans = dp[n - 1][0];
        for(int k = 1; k < 4; ++k)
            ans = min(ans, dp[n - 1][k]);
        return ans;
    }
};
