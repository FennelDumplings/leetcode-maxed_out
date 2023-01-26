// prob1246: Palindrome Removal

/*
 * https://leetcode-cn.com/problems/palindrome-removal/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minimumMoves(vector<int>& arr) {
        if(arr.empty()) return 0;
        int n = arr.size();
        if(n == 1) return 1;
        vector<vector<int>> dp(n, vector<int>(n, n));
        for(int i = 0; i < n; ++i)
        {
            dp[i][i] = 1;
            if(i == n - 1)
                continue;
            if(arr[i] != arr[i + 1])
                dp[i][i + 1] = 2;
            else
                dp[i][i + 1] = 1;
        }
        for(int len = 3; len <= n; ++len)
            for(int i = 0; i <= n - len; ++i)
            {
                int j = i + len - 1;
                if(arr[i] == arr[j])
                    dp[i][j] = dp[i + 1][j - 1];
                for(int k = i; k < j; ++k)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        return dp[0][n - 1];
    }
};
