// prob1220: Count Vowels Permutation

/*
 * https://leetcode-cn.com/problems/count-vowels-permutation/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int countVowelPermutation(int n) {
        D = vector<vector<int>>{
            {0, 1, 0, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 1},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0}
        };
        vector<vector<int>> dp(5, vector<int>(n + 1));
        for(int i = 0; i < 5; ++i)
            dp[i][1] = 1;
        for(int k = 2; k <= n; ++k)
        {
            for(int i = 0; i < 5; ++i)
            {
                for(int j = 0; j < 5; ++j)
                    if(D[i][j] == 1)
                        dp[i][k] = (dp[i][k] + (ll)dp[j][k - 1]) % MOD;
            }
        }
        int ans = 0;
        for(int i = 0; i < 5; ++i)
            ans = (ans + (ll)dp[i][n]) % MOD;
        return ans;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    vector<vector<int>> D;
};
