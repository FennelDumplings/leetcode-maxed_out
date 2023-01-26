// interview08.11: 硬币

/*
 * https://leetcode-cn.com/problems/coin-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int waysToChange(int n) {
        if(n == 0) return 1;
        using  ll = long long;
        const int MOD = 1e9 + 7;
        vector<ll> dp(n + 1, 0);
        dp[0] = 1;
        const vector<int> v({25, 10, 5, 1});
        int m = v.size();
        for(int i = 0; i < m; ++i)
        {
            for(int j = 1; j <= n; ++j)
                if(j - v[i] >= 0)
                    dp[j] = (dp[j] + dp[j - v[i]]) % MOD;
        }
        return dp[n];
    }
};
