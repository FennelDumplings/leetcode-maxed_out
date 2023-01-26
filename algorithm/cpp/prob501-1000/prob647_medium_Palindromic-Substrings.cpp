// prob647: Palindromic Substrings

/*
 * https://leetcode-cn.com/problems/palindromic-substrings/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for(int i = 0; i < n; ++i)
            dp[i][i]= true;
        int ans = n;
        for(int len = 2; len <= n; ++len)
            for(int i = 0; i <= n - len; ++i)
            {
                int j = i + len - 1;
                dp[i][j] = (s[i] == s[j] && (len == 2 || dp[i + 1][j - 1]));
                if(dp[i][j])
                    ++ans;
            }
        return ans;
    }
};
