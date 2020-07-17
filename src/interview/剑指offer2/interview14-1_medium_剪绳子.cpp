// interview14-1: 剪绳子

/*
 * https://leetcode-cn.com/problems/jian-sheng-zi-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int cuttingRope(int n) {
        if(n == 2) return 1;
        if(n == 3) return 2;
        using ll =  long long;
        const int MOD = 1e9 + 7;
        vector<ll> dp(max(n + 1, 3), -1);
        dp[2] = 2;
        dp[3] = 3;
        for(int i = 4; i <= n; ++i)
            for(int k = 1; k <= i - 2; ++k)
                dp[i] = max((ll)dp[i], (k * (ll)dp[i - k]));
        return dp[n] % MOD;
    }
};

