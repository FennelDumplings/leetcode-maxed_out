// prob1641: Count Sorted Vowel Strings

/*
 * https://leetcode-cn.com/problems/count-sorted-vowel-strings/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> D = {
            {1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1},
            {0, 0, 1, 1, 1},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 0, 1}
        };
        vector<vector<int>> dp(5, vector<int>(n + 1));
        for(int s = 0; s < 5; ++s)
            dp[s][1] = 1;
        for(int i = 2; i <= n; ++i)
        {
            for(int v = 0; v < 5; ++v)
                for(int u = 0; u < 5; ++u)
                {
                    if(D[u][v] == 1)
                        dp[v][i] += dp[u][i - 1];
                }
        }
        int ans = 0;
        for(int s = 0; s < 5; ++s)
            ans += dp[s][n];
        return ans;
    }
};
