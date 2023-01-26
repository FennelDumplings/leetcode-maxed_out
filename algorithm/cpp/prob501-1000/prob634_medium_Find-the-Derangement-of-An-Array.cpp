// prob634: Find the Derangement of An Array

/*
 * https://leetcode-cn.com/problems/find-the-derangement-of-an-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findDerangement(int n) {
        if(n == 1) return 0;
        using ll = long long;
        const int MOD = 1e9 + 7;
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int i = 2; i <= n; ++i)
            dp[i] = ((i - 1) * ((ll)dp[i - 1] + dp[i - 2])) % MOD;
        return dp[n];
    }
};
