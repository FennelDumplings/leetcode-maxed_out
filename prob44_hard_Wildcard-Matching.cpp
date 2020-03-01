// prob44: Wildcard Matching

/*
 * Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 */

/*
 * Note:
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters like ? or *.
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
 * p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 * Example 3:
 * Input:
 * s = "cb"
 * p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
 * Example 4:
 * Input:
 * s = "adceb"
 * p = "*a*b"
 * Output: true
 * Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
 * Example 5:
 * Input:
 * s = "acdcb"
 * p = "a*c?b"
 * Output: false
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 贪心
// 有点难理解
class Solution_optim4 {
public:
    bool isMatch(string s, string p) {
        if(s.empty() && p.empty()) return true;
        if(s.empty() || p.empty()) return false;
        int n = s.size(), m = p.size();
        int i = 0, j = 0;
        int istar = -1, jstar = -1;
        while(i < n)
        {
            if(j < m && (s[i] == p[j] || p[j] == '?'))
            {
                ++i;
                ++j;
            }
            else if(j < m && p[j] == '*')
            {
                istar = i;
                jstar = j;
                ++j;
            }
            else if(istar >= 0)
            {
                ++istar;
                i = istar;
                j = jstar + 1;
            }
            else
                return false;
        }
        while(j < m)
            if(p[j++] != '*')
                return false;
        return true;
    }
};

// dp[i][j]:= s[i..n], p[j..m] 是否匹配
// bool[m-1] 换成 vector<bool>: 32ms -> 100ms
class Solution_optim3 {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<bool> dp(m + 1, false);
        dp[m] = true;
        for (int j = m - 1; j >= 0; j--) {
            dp[j] = p[j] == '*' ? dp[j + 1] : false;
        }

        for (int i = n - 1; i >= 0; --i) {
            bool oldright = dp[m];
            // oldright 在 ij 图上保存的是什么位置需要画清楚
            for (int j = m - 1; j >= 0; --j) {
                if (s[i] == p[j] || p[j] == '?') {
                    int temp = dp[j];
                    dp[j] = oldright;
                    oldright = temp;
                }
                else if (p[j] == '*') {
                    int temp = dp[j];
                    dp[j] = dp[j] || dp[j+1];
                    oldright = temp;
                }
                else
                {
                    oldright = dp[j];
                    dp[j] = false;
                }
            }
            dp[m] = false;
        }
        return dp[0];
    }
};

// p[j] = '*' 时 dp[i][j] = dp[i][j - 1] || dp[i - 1][j] 无需开辅助数组记录 p[0..j-1] 是否与 s[0..k] 匹配
// 时间 O(N^2) 空间 O(N^2), 100ms
// 可以考虑用滚动数组优化, 优化到使用O(N)空间后，vector<bool> 改成 bool[] 时间可以快一些，参考optim3
class Solution_optim2 {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();

        vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        // j = 0 的列, 空模式匹配 s, 无需初始化
        // 初始化 i = 0 的行, p 匹配空串
        int j = 1;
        while(j <= m && p[j - 1] == '*')
            dp[0][j++] = true;

        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if(p[j - 1] == '*')
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        return dp[n][m];
    }
};

// 动态规划，开辅助数组记录 p[0..j-1] 是否与 s[0..k] 匹配
// 时间 O(N^2) 空间 O(N^2), 150ms
class Solution_optim1 {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        // 辅助记录 p[0..j-1]是否匹配了s[0..k]
        vector<bool> dp1(m + 1, false);
        dp1[0] = true;

        vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        // j = 0 的列, 空模式匹配 s, 无需初始化
        // 初始化 i = 0 的行, p 匹配空串
        int j = 1;
        while(j <= m && p[j - 1] == '*')
        {
            dp[0][j] = true;
            dp1[j] = true;
            ++j;
        }

        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if(p[j - 1] == '*')
                    dp[i][j] = dp1[j - 1] || dp1[j];
                if(dp[i][j])
                    dp1[j] = true;
            }
        return dp[n][m];
    }
};

// 动态规划，朴素写法
// 时间 O(N^3) 空间 O(N^2), 520ms
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();

        vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        // j = 0 的列, 空模式匹配 s, 无需初始化
        // 初始化 i = 0 的行, p 匹配空串
        int j = 1;
        while(j <= m && p[j - 1] == '*')
            dp[0][j++] = true;

        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if(p[j - 1] == '*')
                    for(int k = i; k >= 0; --k)
                        if(dp[k][j - 1])
                        {
                            dp[i][j] = true;
                            break;
                        }
            }
        return dp[n][m];
    }
};
