// prob72: Edit Distance

/*
 * Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
 * You have the following 3 operations permitted on a word:
 * Insert a character
 * Delete a character
 * Replace a character
 */

/*
 * Example 1:
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation:
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 * Example 2:
 * Input: word1 = "intention", word2 = "execution"
 * Output: 5
 * Explanation:
 * intention -> inention (remove 't')
 * inention -> enention (replace 'i' with 'e')
 * enention -> exention (replace 'n' with 'x')
 * exention -> exection (replace 'n' with 'c')
 * exection -> execution (insert 'u')
 */

#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        if(n1 == 0) return n2;
        if(n2 == 0) return n1;
        vector<vector<int> > dp(n1 + 1, vector<int>(n2 + 1, INT_MAX));
        dp[0][0] = 0;
        for(int i = 1; i <= n1; ++i)
            dp[i][0] = i;
        for(int j = 1; j <= n2; ++j)
            dp[0][j] = j;
        //  dp[i][j] := s1[0..i-1], s2[0..j-1] 的方案中的最小值
        for(int i = 1; i <= n1; ++i)
            for(int j = 1; j <= n2; ++j)
            {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1); // 最后一步是加
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1); // 最后一步是删
                if(word1[i - 1] == word2[j - 1])
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]); // 最后一步是改
                else
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1); // 最后一步是改
            }
        return dp[n1][n2];
    }
};
