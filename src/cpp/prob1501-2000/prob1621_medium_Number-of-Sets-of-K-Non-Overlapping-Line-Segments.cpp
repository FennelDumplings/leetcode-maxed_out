// prob1621: Number of Sets of K Non-Overlapping Line Segments

/*
 * https://leetcode-cn.com/problems/number-of-sets-of-k-non-overlapping-line-segments/
 */

#include <vector>

using namespace std;

class Solution_2 {
public:
    int numberOfSets(int n, int K) {
        if(n == K + 1) return 1;
        vector<vector<int>> dp(n + 1, vector<int>(K + 1));
        for(int k = 1; k <= K; ++k)
            dp[k + 1][k] = 1;
        for(int i = 2; i <= n; ++i)
            dp[i][1] = i * (i - 1) / 2;
        for(int k = 2; k <= K; ++k)
            for(int i = k + 2; i <= n; ++i)
            {
                dp[i][k] = dp[i - 1][k];
                for(int l = 1; l <= i - k; ++l)
                    dp[i][k] = (dp[i][k] + (ll)dp[i - l][k - 1]) % MOD;
            }
        return dp[n][K];
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
};

// 推公式优化
class Solution {
public:
    int numberOfSets(int n, int K) {
        if(n == K + 1) return 1;
        vector<vector<int>> dp(n + 1, vector<int>(K + 1));
        for(int k = 1; k <= K; ++k)
            dp[k + 1][k] = 1;
        for(int i = 2; i <= n; ++i)
            dp[i][1] = i * (i - 1) / 2;
        for(int k = 2; k <= K; ++k)
            for(int i = k + 2; i <= n; ++i)
            {
                dp[i][k] = ((ll)dp[i - 1][k] * 2 - (ll)dp[i - 2][k] + dp[i - 1][k - 1]) % MOD;
            }
        return dp[n][K];
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
};
