// interview43: 1～n整数中1出现的次数

/*
 * https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int countDigitOne(int n) {
        if(n == 0) return 0;
        return solve(n);
    }

private:
    int solve(int n)
    {
        vector<int> digits;
        while(n)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
        int m = digits.size();
        vector<vector<int>> dp(m, vector<int>(m, -1));
        int ans = getdp(m - 1, 1, 1, digits, 0, dp);
        return ans;
    }

    int getdp(int pos, int lim, int zero, const vector<int>& digits, int state, vector<vector<int>>& dp)
    {
        // 返回 dp[pos][state]
        if(pos == -1) return state;
        if(!lim && !zero && dp[pos][state] != -1)
            return dp[pos][state];
        int ans = 0;
        int up = lim ? digits[pos] : 9;
        if(zero)
            ans += getdp(pos - 1, 0, 1, digits, 0, dp);
        for(int i = 0; i <= 9; ++i)
        {
            if(i > up)
                break;
            if(i == 0 && zero)
                continue;
            ans += getdp(pos - 1, lim && i == up, 0, digits, state + (i == 1), dp);
        }
        if(!lim && !zero)
            dp[pos][state] = ans;
        return ans;
    }
};
