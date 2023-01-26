// prob10: Regular Expression Matching

/*
 *
 * Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 */

/*
 * Note:
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters like . or *.
 */

/*
 * Example 1:
 * Input:
 * s = "aa"
 * p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 * Example 2:
 * Input:
 * s = "aa"
 * p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
 * Example 3:
 * Input:
 * s = "ab"
 * p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 * Example 4:
 * Input:
 * s = "aab"
 * p = "c*a*b"
 * Output: true
 * Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
 * Example 5:
 * Input:
 * s = "mississippi"
 * p = "mis*is*p*."
 * Output: false
 */

#include <string>
#include <vector>

using namespace std;

// dp[i][j] := p[0..j] 是否能匹配 s[0..i]
// dp[i][j] =
//     s[i] == p[j]: -> dp[i-1][j-1]
//     s[i] != p[j]:
//         p[j] != '.' or '*' -> false
//         p[j] == . -> dp[i-1][j-1]
//         p[j] == '*':
//             p[j-1] == '*' -> false
//             p[j-1] == s[i] -> dp[k][j-2]中是否有一个为true  k: l-1..i, l是满足s[t]==p[j-1]的最小的 t 这里要注意
//             p[j-1] != s[i] 且 p[j-1] != '.' -> dp[i][j-2] 这里要注意
//             p[j-1] == '.' -> dp[k][j-2]中是否有一个为true k属于[0,i]
// 初始化 dp[0..n][0..n]=false
//     dp[0][0] = true
//     dp[0][j] = p[j] == * 且 p[j - 1] != * -> dp[0][j - 2]
// 迭代 i: 1..n; j: 2..n;
// 答案：dp[n][n]
class Solution {
public:
    bool isMatch(string s, string p) {
        if(s.empty() && p.empty()) return true;
        if(!s.empty() && p.empty()) return false;

        int n = s.size(), m = p.size();
        vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for(int j = 2; j <= m; j += 2)
            if(p[j - 1] == '*')
            {
                if(p[j - 2] != '*')
                    dp[0][j] = dp[0][j - 2];
                else
                    return false; // 剪枝
            }

        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(p[j - 1] == s[i - 1] || p[j - 1] == '.')
                    dp[i][j] = dp[i - 1][j - 1];
                else if(p[j - 1] == '*')
                {
                    if(p[j - 2] == '*')
                        return false; // 剪枝
                    // 两个地方易错
                    if(p[j - 2] == s[i - 1])
                    {
                        // 第一个
                        int k = i;
                        while(k >= 1 && s[k - 1] == p[j - 2])
                        {
                            if(dp[k][j-2])
                            {
                                dp[i][j] = dp[k][j - 2];
                                break;
                            }
                            --k;
                        }
                        if(dp[k][j - 2])
                            dp[i][j] = dp[k][j - 2];
                    }
                    else if(p[j - 2] == '.')
                    {
                        // 第二个
                        for(int k = 0; k <= i; ++k)
                            if(dp[k][j - 2])
                            {
                                dp[i][j] = true;
                                break;
                            }
                    }
                    else if(p[j - 2] != '*')
                        dp[i][j] = dp[i][j - 2];
                }
            }
        return dp[n][m];
    }
};

// from 塔罗兔
class Solution_2 {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j)
            {
                if(i == 0 && j == 0)
                {
                    dp[i][j] = true;
                    continue;
                }
                if(i > 0 && j > 0 && dp[i - 1][j - 1])
                    dp[i][j] = helper(s, p, i, j);
                if(j > 0 && p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j] || dp[i][j - 2];
                    dp[i][j] = dp[i][j] || (i > 0 && dp[i - 1][j] && helper(s, p, i, j - 1));
                }
            }
        return dp[n][m];
    }

private:
    bool helper(const string& s, const string& p, int i, int j)
    {
        return (s[i - 1] == p[j - 1]) || (p[j - 1] == '.');
    }
};

// 状态转移改写, 要把图划清楚才能理解
class Solution_3 {
public:
    bool isMatch(string s, string p) {
        if(s.empty() && p.empty()) return true;
        if(!s.empty() && p.empty()) return false;

        int n = s.size(), m = p.size();
        vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for(int j = 2; j <= m; j += 2)
            if(p[j - 1] == '*')
            {
                if(p[j - 2] != '*')
                    dp[0][j] = dp[0][j - 2];
                else
                    return false; // 剪枝
            }

        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(p[j - 1] == s[i - 1] || p[j - 1] == '.')
                    dp[i][j] = dp[i - 1][j - 1];
                else if(p[j - 1] == '*')
                {
                    if(p[j - 2] == '*')
                        return false; // 剪枝
                    dp[i][j] = dp[i][j - 2];
                    if(p[j - 2] == s[i - 1] || p[j - 2] == '.')
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        return dp[n][m];
    }
};
