// prob516: Longest Palindromic Subsequence

/*
 * Given a string s, find the longest palindromic subsequence's length in s.
 * You may assume that the maximum length of s is 1000.
 */

/*
 * Example 1:
 * Input:
 * "bbbab"
 * Output:
 * 4
 * One possible longest palindromic subsequence is "bbbb".
 * Example 2:
 * Input:
 * "cbbd"
 * Output:
 * 2
 * One possible longest palindromic subsequence is "bb".
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        if(n == 1) return 1;
        vector<vector<int> > dp(n, vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;
        for(int j = 1; j < n; ++j)
            for(int i = j - 1; i >= 0; --i)
            {
                if(s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        return dp[0][n - 1];
    }
};
