// interview19: 正则表达式匹配

/*
 * https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        if(s.empty() && p.empty()) return true;
        if(!s.empty() && p.empty()) return false;
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for(int j = 2; j <= m; j += 2)
            if(p[j - 1] == '*')
            {
                if(p[j - 2] != '*')
                    dp[0][j] = dp[0][j - 2];
                else
                    return false;
            }
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(p[j - 1] != '*')
                {
                    dp[i][j] = ((p[j - 1] == '.') || (p[j - 1] == s[i - 1])) && dp[i - 1][j - 1];
                }
                else
                {
                    if(j == 1) return false;
                    if(p[j - 2] == '*')
                        return false;
                    dp[i][j] = dp[i][j - 2];
                    if(p[j - 2] == s[i - 1] || p[j - 2] == '.')
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        return dp[n][m];
    }
};
