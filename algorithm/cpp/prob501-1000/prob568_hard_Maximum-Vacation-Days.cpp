// prob568: Maximum Vacation Days

/*
 * https://leetcode-cn.com/problems/maximum-vacation-days/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int N = days.size();
        int K = days[0].size();
        // days : N * K
        vector<vector<int>> dp(N, vector<int>(K, 0));
        vector<vector<int>> &adj = flights;
        for(int i = 0; i < N; ++i)
            dp[i][K - 1] = days[i][K - 1];
        for(int k = K - 2; k >= 0; --k)
            for(int i = 0; i < N; ++i)
            {
                dp[i][k] = dp[i][k + 1]; // 不坐航班
                for(int j = 0; j < N; ++j)
                {
                    if(adj[i][j] == 1)
                        dp[i][k] =  max(dp[i][k], dp[j][k + 1]);
                }
                dp[i][k] += days[i][k];
            }
        int ans = dp[0][0];
        for(int start = 1; start < N; ++start)
        {
            if(adj[0][start] == 1)
                ans = max(ans, dp[start][0]);
        }
        return ans;
    }
};
