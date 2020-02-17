// prob664: Strange Printer

/*
 * There is a strange printer with the following two special requirements:
 * 1. The printer can only print a sequence of the same character each time.
 * 2. At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.
 * Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.
 */

/*
 * Example 1:
 * Input: "aaabbb"
 * Output: 2
 * Example 2:
 * Input: "aba"
 * Output: 2
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int strangePrinter(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<vector<int> > dp(n + 1, vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;

        for(int r = 1; r < n; ++r)
            for(int l = r - 1; l >= 0; --l)
            {
                dp[l][r] = dp[l + 1][r] + 1;
                for(int i = l + 1; i <= r; ++i)
                    if(s[i] == s[l])
                    {
                        // 访问 dp[i + 1][r], 此时 i 最大可以是 r, r 最大可以是 n-1, 所以 dp 要开 n+1 行
                        dp[l][r] = min(dp[l][r], dp[l + 1][i] + dp[i + 1][r]);
                    }
            }
        return dp[0][n - 1];
    }
};
