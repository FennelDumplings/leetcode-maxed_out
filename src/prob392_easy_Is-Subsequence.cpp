// prob392: Is Subsequence

/*
 * Given a string s and a string t, check if s is subsequence of t.
 * You may assume that there is only lower case English letters in both s and t. t is potentially a very long (length ~= 500,000) string,
 * and s is a short string (<=100).
 * A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters
 * without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).
 */

/*
 * Example 1:
 * s = "abc", t = "ahbgdc"
 * Return true.
 * Example 2:
 * s = "axc", t = "ahbgdc"
 * Return false.
 */

/*
 * Follow up:
 * If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence.
 * In this scenario, how would you change your code?
 */

#include <string>
#include <vector>

using namespace std;

class Solution_2 {
public:
    bool isSubsequence(string s, string t) {
        int ns = s.size(), nt = t.size();
        if(ns == 0) return true;
        if(nt == 0) return false;
        if(ns > nt) return false;
        int is = 0;
        for(int it = 0; it < nt; ++it)
        {
            if(t[it] == s[is])
            {
                ++is;
                if(is == ns) return true;
            }
        }
        return false;
    }
};


class Solution_3 {
public:
    bool isSubsequence(string s, string t) {
        // dp[i][j] := s[0..i-1] 是否是 t[0..j-1] 的子序列
        // dp[0][0..m] = true
        // dp[1..n][0] = false
        // dp[i][j] = dp[i][j-1] || (dp[i - 1][j - 1] && s[i-1] == t[j-1])
        int n = s.size(), m = t.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        for(int j = 0; j <= m; ++j)
            dp[0][j] = true;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                dp[i][j] = dp[i][j - 1] || (dp[i - 1][j - 1] && s[i - 1] == t[j - 1]);
        return dp[n][m];
    }
};

#include <algorithm>

class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> mappings(26);
        int m = t.size();
        for(int i = 0; i < m; ++i)
            mappings[t[i] - 'a'].push_back(i);
        int n = s.size();
        int prev = 0;
        for(int i = 0; i < n; ++i)
        {
            const vector<int> &idxs = mappings[s[i] - 'a'];
            auto it = lower_bound(idxs.begin(), idxs.end(), prev);
            if(it == idxs.end())
                return false;
            prev = *it + 1;
        }
        return true;
    }
};
