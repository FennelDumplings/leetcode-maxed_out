// prob639: Decode Ways II

/*
 * https://leetcode-cn.com/problems/decode-ways-ii/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n + 1, 0);
        dp[n] = 1;
        if(s[n - 1] == '*')
            dp[n - 1] = 9;
        else if(s[n - 1] != '0')
            dp[n - 1] = 1;
        using ll = long long;
        const int MOD = 1e9 + 7;
        for(int i = n - 2; i >= 0; --i)
        {
            if(s[i] == '0') continue;

            int a; // s[i] = 1
            if(s[i + 1] == '*')
                a = (dp[i + 1] + (ll)dp[i + 2] * 9) % MOD;
            else
                a = (dp[i + 1] + (ll)dp[i + 2]) % MOD;
            int b; // s[i] = 2
            if(s[i + 1] == '*')
                b = (dp[i + 1] + (ll)dp[i + 2] * 6) % MOD;
            else if(s[i + 1] >= '0' && s[i + 1] <= '6')
                b = (dp[i + 1] + (ll)dp[i + 2]) % MOD;
            else
                b = dp[i + 1];
            int c = dp[i + 1]; // s[i] = 3~9

            if(s[i] == '1')
                dp[i] = a;
            if(s[i] == '2')
                dp[i] = b;
            if(s[i] >= '3' && s[i] <= '9')
                dp[i] = c;
            if(s[i] == '*')
                dp[i] = (a + (ll)b + (ll)c * 7) % MOD;
        }
        return dp[0];
    }
};
