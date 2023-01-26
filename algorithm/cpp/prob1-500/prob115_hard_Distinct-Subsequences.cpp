// prob115: Distinct Subsequences

/*
 * Given a string S and a string T, count the number of distinct subsequences of S which equals T.
 * A subsequence of a string is a new string which is formed from the original
 * string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining
 * characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        using ll = long long;
        if(s.empty()) return 0;
        if(t.empty()) return -1;
        int n = s.size(), m = t.size();
        vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));
        for(int i = 0; i <= n; ++i) dp[i][0] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if(s[i - 1] == t[j - 1])
                    dp[i][j] += (ll)dp[i - 1][j - 1];

            }
        return dp[n][m];
    }
};
