// prob629: K Inverse Pairs Array

/*
 * https://leetcode-cn.com/problems/k-inverse-pairs-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int kInversePairs(int n, int k) {
        if(k == 0)
            return 1;
        if(n == 1)
            return 0;
        const int MOD = 1e9 + 7;
        using ll = long long;
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        for(int i = 1; i <= n; ++i)
            dp[i][0] = 1;
        dp[2][1] = 1;
        for(int i = 3; i <= n; ++i)
            for(int j = 1; j <= k; ++j)
            {
                // 已有 1,2,...,i-1 排列，共 i-1 (0,1,...,i-2)
                dp[i][j] = dp[i - 1][j]; // 将 i 加在末尾
                for(int l = max(0, i - 1 - j); l <= i - 2; ++l)
                {
                    // 插入在 l (0, 1, ..., i - 2)
                    // 产生 (i - 1) - l 个
                    // j - ((i - 1) - l) > 0
                    dp[i][j] = (dp[i][j] + (ll)dp[i - 1][j - ((i - 1) - l)]) % MOD;
                }
            }
        return dp[n][k];
    }
};

// 公式变形
class Solution_2 {
public:
    int kInversePairs(int n, int k) {
        if(k == 0)
            return 1;
        if(n == 1)
            return 0;
        const int MOD = 1e9 + 7;
        using ll = long long;
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        for(int i = 1; i <= n; ++i)
            dp[i][0] = 1;
        dp[2][1] = 1;
        for(int i = 3; i <= n; ++i)
            for(int j = 1; j <= k; ++j)
            {
                dp[i][j] = (dp[i][j - 1] + (ll)dp[i - 1][j]) % MOD;
                if(j >= i)
                    dp[i][j] = ((ll)dp[i][j] - dp[i - 1][j - i] + MOD) % MOD;
            }
        return dp[n][k];
    }
};
