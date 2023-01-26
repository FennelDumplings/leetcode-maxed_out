// prob583: Delete Operation for Two Strings

/*
 * Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same,
 * where in each step you can delete one character in either string.
 */

/*
 * Note:
 * The length of given words won't exceed 500.
 * Characters in given words can only be lower-case letters.
 */

/*
 * Example 1:
 * Input: "sea", "eat"
 * Output: 2
 * Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
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
        for(int i = 1; i <= n1; ++i)
            for(int j = 1; j <= n2; ++j)
            {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                if(word1[i - 1] == word2[j - 1])
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            }
        return dp[n1][n2];
    }
};

// 滚动数组优化
class Solution_2 {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        if(n1 == 0) return n2;
        if(n2 == 0) return n1;
        vector<int> dp(n2 + 1, INT_MAX);
        vector<int> dp_prev(n2 + 1, INT_MAX);
        for(int j = 0; j <= n2; ++j)
            dp_prev[j] = j;
        for(int i = 1; i <= n1; ++i)
        {
            dp[0] = i;
            for(int j = 1; j <= n2; ++j)
            {
                dp[j] = min(dp_prev[j] + 1, dp[j - 1] + 1);
                if(word1[i - 1] == word2[j - 1])
                    dp[j] = min(dp[j], dp_prev[j - 1]);
            }
            dp_prev = dp;
        }
        return dp[n2];
    }
};

