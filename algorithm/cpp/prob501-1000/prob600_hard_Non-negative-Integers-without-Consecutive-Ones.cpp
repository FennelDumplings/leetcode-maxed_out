// prob600: Non-negative Integers without Consecutive Ones

/*
 * https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findIntegers(int num) {
        int ans = solve(num);
        return ans;
    }

private:
    int solve(int n)
    {
        // [0..n]
        vector<int> digits;
        while(n)
        {
            digits.push_back(n % 2);
            n /= 2;
        }
        int m = digits.size();
        vector<vector<int>> dp(m, vector<int>(2, -1));
        int ans = getdp(m - 1, 1, 1, 2, digits, dp);
        return ans;
    }

    int getdp(int pos, int lim, int zero, int pre, const vector<int>& digits, vector<vector<int>>& dp)
    {
        if(pos == -1) return 1; // 0 是合法的
        if(!lim && !zero && dp[pos][pre] != -1)
            return dp[pos][pre];
        int up = lim ? digits[pos] : 1;
        int ans = 0;
        if(zero)
            ans += getdp(pos - 1, 0, 1, 0, digits, dp);
        for(int i = 0; i <= 1; ++i)
        {
            if(i > up) break;
            if(zero && i == 0) continue;
            if(pre == 1 && i == 1) continue;
            ans += getdp(pos - 1, lim && i == up, 0, i, digits, dp);
        }
        if(!lim && !zero)
            dp[pos][pre] = ans;
        return ans;
    }
};
