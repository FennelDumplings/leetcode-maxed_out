// prob91: Decode Ways

/*
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given a non-empty string containing only digits, determine the total number of ways to decode it.
 */

/*
 * Example 1:
 * Input: "12"
 * Output: 2
 * Explanation: It could be decoded as "AB" (1 2) or "L" (12).
 * Example 2:
 * Input: "226"
 * Output: 3
 * Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        // 调用方保证非空
        int n = s.size();
        if(n == 1)
        {
            if(s[0] == '0') return 0;
            else return 1;
        }
        // n >= 2
        vector<int> dp(n + 1, 0);
        dp[n] = 1;
        if(s[n - 1] != '0') dp[n - 1] = 1;
        for(int i = n - 2; i >= 0; --i)
        {
            if(s[i] == '1')
                dp[i] = dp[i + 1] + dp[i + 2];
            else if(s[i] == '2' && s[i + 1] - '0' <= 6)
                dp[i] = dp[i + 1] + dp[i + 2];
            else if(s[i] == '2' && s[i + 1] - '0' > 6)
                dp[i] = dp[i + 1];
            else if(s[i] != '0')
                dp[i] = dp[i + 1];
        }
        return dp[0];
    }
};
