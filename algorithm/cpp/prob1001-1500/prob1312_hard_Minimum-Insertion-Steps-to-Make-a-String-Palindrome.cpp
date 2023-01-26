// prob1312: Minimum Insertion Steps to Make a String Palindrome

/*
 * Given a string s. In one step you can insert any character at any index of the string.
 * Return the minimum number of steps to make s palindrome.
 * A Palindrome String is one that reads the same backward as well as forward.
 */

/*
 * Example 1:
 * Input: s = "zzazz"
 * Output: 0
 * Explanation: The string "zzazz" is already palindrome we don't need any insertions.
 * Example 2:
 * Input: s = "mbadm"
 * Output: 2
 * Explanation: String can be "mbdadbm" or "mdbabdm".
 * Example 3:
 * Input: s = "leetcode"
 * Output: 5
 * Explanation: Inserting 5 characters the string becomes "leetcodocteel".
 * Example 4:
 * Input: s = "g"
 * Output: 0
 * Example 5:
 * Input: s = "no"
 * Output: 1
 */

/*
 * Constraints:
 * 1 <= s.length <= 500
 * All characters of s are lower case English letters.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int> > dp(n, vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;
        for(int len = 2; len <= n; ++len)
        {
            for(int i = 0; i + len - 1 < n; ++i)
            {
                int j = i + len - 1;
                if(s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
            }
        }
        return s.size() - dp[0][n - 1];
    }
};
