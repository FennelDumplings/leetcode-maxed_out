// prob712: Minimum ASCII Delete Sum for Two Strings

/*
 * Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.
 */

/*
 * Example 1:
 * Input: s1 = "sea", s2 = "eat"
 * Output: 231
 * Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
 * Deleting "t" from "eat" adds 116 to the sum.
 * At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
 * Example 2:
 * Input: s1 = "delete", s2 = "leet"
 * Output: 403
 * Explanation: Deleting "dee" from "delete" to turn the string into "let",
 * adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
 * At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
 * If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
 */

/*
 * Note:
 * 0 < s1.length, s2.length <= 1000.
 * All elements of each string will have an ASCII value in [97, 122].
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<int> > dp_len(n1, vector<int>(n2, 0));
        vector<vector<int> > dp_ascii(n1, vector<int>(n2, 0));
        int result = (int)s1[0] + (int)s2[0];
        if(s1[0] == s2[0])
        {
            dp_len[0][0] = 1;
            dp_ascii[0][0] = (int)s1[0] + (int)s2[0];
        }
        for(int i = 1; i < n1; ++i)
        {
            result += (int)s1[i];
            if(s1[i] == s2[0])
            {
                dp_len[i][0] = 1;
                dp_ascii[i][0] = (int)s1[i] + (int)s2[0];
            }
            else
            {
                dp_len[i][0] = dp_len[i - 1][0];
                dp_ascii[i][0] = dp_ascii[i - 1][0];
            }
        }
        for(int j = 1; j < n2; ++j)
        {
            result += (int)s2[j];
            if(s1[0] == s2[j])
            {
                dp_len[0][j] = 1;
                dp_ascii[0][j] = (int)s1[0] + (int)s2[j];
            }
            else
            {
                dp_len[0][j] = dp_len[0][j - 1];
                dp_ascii[0][j] = dp_ascii[0][j - 1];
            }
        }
        for(int i = 1; i < n1; ++i)
            for(int j = 1; j < n2; ++j)
            {
                if(s1[i] == s2[j])
                {
                    dp_len[i][j] = dp_len[i - 1][j - 1] + 1;
                    dp_ascii[i][j] = dp_ascii[i - 1][j - 1] + (int)s1[i] + (int)s2[j];
                }
                else
                {
                    if(dp_len[i - 1][j] > dp_len[i][j - 1])
                    {
                        dp_len[i][j] = dp_len[i - 1][j];
                        dp_ascii[i][j] = dp_ascii[i - 1][j];
                    }
                    else if(dp_len[i][j - 1] > dp_len[i - 1][j])
                    {
                        dp_len[i][j] = dp_len[i][j - 1];
                        dp_ascii[i][j] = dp_ascii[i][j - 1];
                    }
                    else
                    {
                        dp_len[i][j] = dp_len[i][j - 1];
                        dp_ascii[i][j] = max(dp_ascii[i][j - 1], dp_ascii[i - 1][j]);
                    }
                }
            }
        result -= dp_ascii[n1 - 1][n2 - 1];
        return result;
    }
};
