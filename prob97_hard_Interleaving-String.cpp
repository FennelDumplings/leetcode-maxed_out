// prob97: Interleaving String

/*
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 */

/*
 * Example 1:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 * Output: true
 * Example 2:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 * Output: false
 */

#include <string>
#include <vector>

using namespace  std;

// dp[i][j]:=A[0..i-1],B[0..j-1]与C[0..i+j-1]是否满足
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if(n1 + n2 != n3) return false;
        vector<vector<bool> > dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        for(int i = 0; i <= n1; ++i)
            for(int j = 0; j <= n2; ++j)
            {
                if(i == 0 && j == 0) continue;
                // i >= 1, j >= 1 至少一个成立
                bool cur = false;
                if(i - 1 >= 0 && s3[i + j - 1] == s1[i - 1])
                    cur = cur || dp[i - 1][j];
                if(j - 1 >= 0 && s3[i + j - 1] == s2[j - 1])
                    cur = cur || dp[i][j - 1];
                dp[i][j] = cur;
            }
        return dp[n1][n2];
    }
};
