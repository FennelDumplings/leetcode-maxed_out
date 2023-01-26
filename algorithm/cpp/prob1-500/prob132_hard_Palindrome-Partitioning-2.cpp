// prob132: Palindrome Partitioning

/*
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 */

/*
 * Example:
 * Input: "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
 */

#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minCut(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        if(n == 1) return 1;
        vector<vector<bool> > c(n, vector<bool>(n, false));
        c[n - 1][n - 1] = true;
        for(int i = 0; i < n - 1; ++i)
        {
            c[i][i] = true;
            c[i + 1][i] = true;
        }
        for(int j = 1; j < n; ++j)
            for(int i = j - 1; i >= 0; --i)
                if(s[i] == s[j])
                    c[i][j] = c[i + 1][j - 1];

        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for(int i = 2; i <= n; ++i)
        {
            int minx = INT_MAX;
            for(int j = 1; j <= i; ++j)
            {
                if(c[j - 1][i - 1])
                    minx = min(minx, dp[j - 1]);
            }
            dp[i] = minx + 1;
        }
        return dp[n];
    }
};
