// prob1359: Count All Valid Pickup and Delivery Options

/*
 * https://leetcode-cn.com/problems/count-all-valid-pickup-and-delivery-options/
 */

// dp[i] = (2i - 1 + C(2i - 1, 2))
// dp[1] = 1
// dp[2] = (3 + C(3, 2)) = 6

using ll = long long;

const int MOD = 1e9 + 7;

class Solution {
public:
    int countOrders(int n) {
        if(n == 1) return 1;
        ll dp = 1;
        for(int i = 2; i <= n; ++i)
        {
            dp = ((i * 2 - 1 + (i * 2 - 2) * (i * 2 - 1) / 2) * dp) % MOD;
        }
        return dp;
    }
};
