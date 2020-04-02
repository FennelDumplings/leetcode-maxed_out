// prob5: Longest Palindromic Substring

/*
 * Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 */

/*
 * Example 1:
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 * Example 2:
 * Input: "cbbd"
 * Output: "bb"
 */

#include <string>
#include <vector>

using namespace std;

// 暴力枚举回文串中心
class Solution {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        int n = s.size();
        if(n == 1) return s;

        int max_len = 1;
        int start = 0;
        for(int i = 0; i < n; ++i)
        {
            // while 循环提前终止，相当于剪枝了一些状态
            int len1 = 1; // s[i] 为中心点的最长回文子串长
            int l = i - 1, r = i + 1;
            while(l >= 0 && r <= n - 1 && s[l] == s[r])
            {
                len1 += 2;
                ++r;
                --l;
            }
            if(len1 > max_len)
            {
                max_len = len1;
                start = l + 1;
            }
            int len2 = 0; // s[i], s[i - 1] 为中心点的最长回文子串长
            l = i - 1;
            r = i;
            while(l >= 0 && r <= n - 1 && s[l] == s[r])
            {
                len2 += 2;
                ++r;
                --l;
            }
            if(len2 > max_len)
            {
                max_len = len2;
                start = l + 1;
            }
        }
        return s.substr(start, max_len);
    }
};

// DP: 朴素DP, 显式的开空间
// dp[i][j] := dp[i][j] 是否是回文子串
// dp[i][j] = 0   (s[i] != s[j])
//          = dp[i + 1][j - 1]   (s[i] == s[j])
// dp[i][i] = 1
// 时空效率都远低于暴力枚举
class Solution_2 {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        int n = s.size();
        if(n == 1) return s;

        int max_length = 1;
        int max_i = 0;
        vector<vector<bool> > dp(n, vector<bool>(n, 0));
        for(int i = 0; i < n; ++i)
        {
            dp[i][i] = true;
            if(i < n - 1)
                dp[i + 1][i] = true; // 处理 bb 这种情况的转移
        }

        for(int j = 1; j < n; ++j)
            for(int i = j - 1; i >= 0 ; --i)
            {
                // 没有隐含剪枝，速度没有暴力枚举快
                int len = j - i + 1;
                if(s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1];
                if(dp[i][j] && len > max_length)
                {
                    max_i = i;
                    max_length = len;
                }
            }
        return s.substr(max_i, max_length);
    }
};
