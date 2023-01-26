// interview08.14: 布尔运算

/*
 * https://leetcode-cn.com/problems/boolean-evaluation-lcci/
 */

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countEval(string s, int result) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
        solve(s, 0, n - 1, dp);
        return dp[0][n - 1][result];
    }

private:
    void solve(const string& s, int left, int right, vector<vector<vector<int>>>& dp)
    {
        // [left,                         right]
        // [      it_left,    it_right         ]
        if(dp[left][right][0] != -1)
            return;
        dp[left][right][0] = 0;
        dp[left][right][1] = 0;
        if(left == right)
        {
            dp[left][right][s[left] - '0'] = 1;
            return;
        }
        for(int i = left + 1; i < right; i += 2)
        {
            solve(s, left, i - 1, dp);
            solve(s, i + 1, right, dp);
            for(int x: {0, 1})
                for(int y: {0, 1})
                {
                    if(s[i] == '|')
                        dp[left][right][x | y] += dp[left][i - 1][x] * dp[i + 1][right][y];
                    else if(s[i] == '&')
                        dp[left][right][x & y] += dp[left][i - 1][x] * dp[i + 1][right][y];
                    else if(s[i] == '^')
                        dp[left][right][x ^ y] += dp[left][i - 1][x] * dp[i + 1][right][y];
                }
        }
    }
};
