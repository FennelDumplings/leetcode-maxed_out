// interview49: 丑数

/*
 * https://leetcode-cn.com/problems/chou-shu-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        // n > 1;
        vector<int> dp(n + 1, -1);
        dp[1] = 1;
        int i2 = 1, i3 = 1, i5 = 1;
        for(int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i2] * 2;
            dp[i] = min(dp[i3] * 3, dp[i]);
            dp[i] = min(dp[i5] * 5, dp[i]);
            if(dp[i] == dp[i2] * 2) ++i2;
            if(dp[i] == dp[i3] * 3) ++i3;
            if(dp[i] == dp[i5] * 5) ++i5;
        }
        return dp[n];
    }
};
