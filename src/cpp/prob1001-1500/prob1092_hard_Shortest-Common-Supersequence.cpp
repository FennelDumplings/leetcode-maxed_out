// prob1092: Shortest Common Supersequence

/*
 * Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.  If multiple answers exist, you may return any of them.
 * (A string S is a subsequence of string T if deleting some number of characters from T (possibly 0, and the characters are chosen anywhere from T) results in the string S.)
 */

/*
 * Example 1:
 *
 * Input: str1 = "abac", str2 = "cab"
 * Output: "cabac"
 * Explanation:
 * str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
 * str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
 * The answer provided is the shortest such string that satisfies these properties.
 */

/*
 * Note:
 * 1 <= str1.length, str2.length <= 1000
 * str1 and str2 consist of lowercase English letters.
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(str1[i - 1] == str2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }

        //构造最短公共超序列
        int i, j, lcs_len;
        string ans;
        for (i = n, j = m, lcs_len = dp[n][m]; i || j; )
        {
            if (i && j && str1[i - 1] == str2[j - 1])
            {
                ans.push_back(str1[i - 1]);
                lcs_len--, i--, j--;
            }
            else
            {
                // 若此处只修改 i、j 的值但不记录在 ans 中，则 ans 最后记录的为最长公共子序列
                if (j && dp[i][j - 1] == lcs_len)
                    ans.push_back(str2[--j]);
                    // --j;
                else
                    ans.push_back(str1[--i]);
                    // --i;
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
