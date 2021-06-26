// prob552: Student Attendance Record II

/*
 * https://leetcode-cn.com/problems/student-attendance-record-ii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int checkRecord(int n) {
        const int MOD = 1e9 + 7;
        using ll = long long;
        vector<int> dp(max(n + 1, 4));
        dp[0] = 1;
        dp[1] = 2;
        dp[2] = 4;
        dp[3] = 7;
        for(int i = 4; i <= n; ++i)
            dp[i] = (2 * (ll)dp[i - 1] - dp[i - 4] + MOD) % MOD;
        int ans = dp[n];
        for(int i = 1; i <= n; ++i)
            ans = (ans + (ll)dp[i - 1] * dp[n - i]) % MOD;
        return ans;
    }
};
