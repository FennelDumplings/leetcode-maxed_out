
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n = s.size();
        vector<int> dp(n, 0);
        // dp[i] := 考虑到i ，使得无相邻重复的最低成本
        for(int i = 1; i < n; ++i)
        {
            if(s[i] != s[i - 1])
                dp[i] = dp[i - 1];
            else
            {
                dp[i] = dp[i - 1] + min(cost[i], cost[i - 1]);
                if(cost[i] < cost[i - 1])
                    cost[i] = cost[i - 1];
            }
        }
        return dp[n - 1];
    }
};
