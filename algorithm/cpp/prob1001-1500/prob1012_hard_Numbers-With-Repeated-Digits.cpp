// prob1012: Numbers With Repeated Digits

/*
 * Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.
 */

/*
 * Example 1:
 *
 * Input: 20
 * Output: 1
 * Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
 * Example 2:
 *
 * Input: 100
 * Output: 10
 * Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
 * Example 3:
 *
 * Input: 1000
 * Output: 262
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/numbers-with-repeated-digits
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/*
 * Note:
 * 1 <= N <= 10^9
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numDupDigitsAtMostN(int N) {
        int ans = N - solve(N);
        return ans;
    }

private:
    int solve(int N)
    {
        // [0, N] 之间的个数, 0 不合法
        vector<int> digits;
        while(N)
        {
            digits.push_back(N % 10);
            N /= 10;
        }
        int m = digits.size();
        vector<vector<int>> dp(m, vector<int>((1 << 10) - 1, -1)); // dp[pos][state]
        int state = 0;
        int ans = getdp(m - 1, 1, 1, digits, state, dp);
        return ans;
    }

    int getdp(int pos, int lim, int zero, const vector<int>& digits, int& state, vector<vector<int>>& dp)
    {
        if(pos == -1) return !zero;
        if(!lim && !zero && dp[pos][state] != -1)
            return dp[pos][state];
        int ans = 0;
        if(zero)
            ans += getdp(pos - 1, 0, 1, digits, state, dp);
        int up = lim ? digits[pos] : 9;
        for(int i = 0; i <= 9; ++i)
        {
            if(i > up) break;
            if(zero && i == 0) continue;
            if(state & (1 << i)) continue;
            state |= (1 << i);
            ans += getdp(pos - 1, lim && i == up, 0, digits, state, dp);
            state &= ~(1 << i);
        }
        if(!lim && !zero)
            dp[pos][state] = ans;
        return ans;
    }
};
