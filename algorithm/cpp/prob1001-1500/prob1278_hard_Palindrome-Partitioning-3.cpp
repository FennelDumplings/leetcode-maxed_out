// prob1278: Palindrome Partitioning III

/*
 * https://leetcode-cn.com/problems/palindrome-partitioning-iii/
 */

#include <string>
#include <vector>

using namespace std;

// dp1[i][j] := [i..j] 变为回文串的最少修改次数
// 全初始化为 0
// dp1[i][j] = dp[i + 1][j - 1] + 1  s[i] != s[j]
//             dp[i + 1][j - 1]      s[i] == s[j]

// dp2[i][k] := [0..i] 分 k 个，最少的修改次数
// i + 1 >= k
// dp2[0][1] = 0
// dp2[i][k] = min{
//      dp1[0][i]                            k == 1
//      dp2[j - 1][k - 1] + dp1[j][i]    k > 1 && 0 < j <= i
//                                       && j - 1 + 1 >= k - 1
// }

class Solution {
public:
    int palindromePartition(string s, int K) {
        int n = s.size();
        vector<vector<int>> dp1(n, vector<int>(n, 0));
        for(int len = 2; len <= n; ++len)
            for(int i = 0; i <= n - len; ++i)
            {
                int j = i + len - 1;
                dp1[i][j] = dp1[i + 1][j - 1];
                if(s[i] != s[j])
                    ++dp1[i][j];
            }
        vector<vector<int>> dp2(n, vector<int>(K + 1, n));
        for(int i = 0; i < n; ++i)
            dp2[i][1] = dp1[0][i];
        for(int k = 2; k <= K; ++k)
        {
            for(int i = k - 1; i < n; ++i)
            {
                // dp2[i][k]
                for(int j = k - 1; j <= i; ++j)
                    dp2[i][k] = min(dp2[i][k], dp2[j - 1][k - 1] + dp1[j][i]);
            }
        }
        return dp2[n - 1][K];
    }
};
