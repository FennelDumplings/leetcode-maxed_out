// prob1420: Build Array Where You Can Find The Maximum Exactly K Comparisons

/*
 * https://leetcode-cn.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/
 */

#include <vector>

using namespace std;

using ll = long long;

int quick_pow(int a, int n, int p)
{
    if(a == 0) return 0;
    int ans = 1;
    while(n)
    {
        if(n & 1)
            ans = (ans * (ll)a) % p;
        a = (a * (ll)a) % p;
        n >>= 1;
    }
    return ans;
}

class Solution {
public:
    int numOfArrays(int n, int m, int K) {
        if(n < K || m < K) return 0;
        dp = VVV(n, VV(m + 1, vector<int>(K + 1, -1)));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= m; ++j)
            {
                dp[i][j][0] = quick_pow(j, n - i, MOD);
                for(int k = 0; k <= K; ++k)
                {
                    if(n - i < k || m - j < k)
                        dp[i][j][k] = 0;
                    else if(i == n - 1 && k == 1)
                        dp[i][j][k] = m - j;
                }
            }
        return solve(m, 0, 0, K);
    }

private:
    using VV = vector<vector<int>>;
    using VVV = vector<VV>;
    VVV dp;
    const int MOD = 1e9 + 7;

    int solve(const int m, int i, int j, int k)
    {
        if(dp[i][j][k] != -1)
            return dp[i][j][k];
        dp[i][j][k] = 0;
        dp[i][j][k] += (j * (ll)solve(m, i + 1, j, k)) % MOD;
        for(int t = j + 1; t <= m; ++t)
            dp[i][j][k] = (dp[i][j][k] + solve(m, i + 1, t, k - 1)) % MOD;
        return dp[i][j][k];
    }
};
