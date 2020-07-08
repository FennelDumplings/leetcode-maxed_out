// prob940: Distinct Subsequences II

/*
 * https://leetcode-cn.com/problems/distinct-subsequences-ii/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int distinctSubseqII(string S) {
        if(S.empty()) return 0;
        int n = S.size();
        if(n == 1) return 1;
        using ll = long long;
        const int MOD = 1e9 + 7;
        vector<int> dp(n + 1, 0);
        // dp[i] := 考虑前 i 个元素，不同的子序列个数
        vector<int> last(26, -1); // 字符上一次出现的位置，转移时有用, -1 表示没出现过
        dp[0] = 1; // 不考虑任何字符时候，有个空串
        for(int i = 1; i <= n; ++i)
        {
            dp[i] = (2 * (ll)dp[i - 1]) % MOD;
            if(last[S[i - 1] - 'a'] >= 1)
                dp[i] = (dp[i] - dp[last[S[i - 1] - 'a'] - 1] + MOD) % MOD;
            last[S[i - 1] - 'a'] = i;
        }
        return dp[n] - 1;
    }
};
