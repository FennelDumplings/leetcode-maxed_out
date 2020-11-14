// prob1216: Valid Palindrome III

/*
 * https://leetcode-cn.com/problems/valid-palindrome-iii/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int l = 2; l <= n; ++l)
        {
            for(int i = 0; i < n - l + 1; ++i)
            {
                int j = i + l - 1;
                if(s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1];
                else
                    dp[i][j] = 1 + min(dp[i][j - 1], dp[i + 1][j]);
            }
        }
        return dp[0][n - 1] <= k;
    }
};
