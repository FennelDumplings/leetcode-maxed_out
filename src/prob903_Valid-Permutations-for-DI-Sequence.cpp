// prob903: Valid Permutations for DI Sequence

/*
 * https://leetcode-cn.com/problems/valid-permutations-for-di-sequence/
 */

#include <vector>
#include <string>

using namespace std;

// dp[i][j] := 已选 p[0]..p[i] 且未选元素中比 p[i] 小的有 j 个
class Solution {
public:
    int numPermsDISequence(string S) {
        int n = S.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        for(int j = 0; j <= n; ++j)
            dp[0][j] = 1;

        for(int i = 1; i <= n; ++i)
            for(int j = 0; j <= i; ++j)
            {
                if(S[i - 1] == 'D')
                {
                    for(int k = j; k < i; ++k)
                    {
                        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                    }
                }
                else
                {
                    for(int k = 0; k < j; ++k)
                    {
                        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                    }
                }
            }

        int ans = 0;
        for(int x: dp[n])
            ans = (ans + x) % MOD;
        return ans;
    }

private:
    const int MOD = 1e9 + 7;
};


// dp[i][j] := 已选 p[0]..p[i] 且未选元素中比 p[i] 小的有 j 个
// 优化
class Solution_2 {
public:
    int numPermsDISequence(string S) {
        int n = S.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        for(int j = 0; j <= n; ++j)
            dp[0][j] = 1;

        for(int i = 1; i <= n; ++i)
            if(S[i - 1] == 'D')
            {
                for(int j = i - 1; j >= 0; --j)
                {
                    dp[i][j] = (dp[i][j + 1] + dp[i - 1][j]) % MOD;
                }
            }
            else
            {
                for(int j = 1; j <= i; ++j)
                {
                    dp[i][j] = (dp[i][j - 1] + dp[i - 1][j - 1]) % MOD;
                }
            }

        int ans = 0;
        for(int x: dp[n])
            ans = (ans + x) % MOD;
        return ans;
    }

private:
    const int MOD = 1e9 + 7;
};
