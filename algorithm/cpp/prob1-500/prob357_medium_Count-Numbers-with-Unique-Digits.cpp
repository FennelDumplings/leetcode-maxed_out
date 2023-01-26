// prob357: Count Numbers with Unique Digits

/*
 * Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.
 */

/*
 * Example:
 * Input: 2
 * Output: 91
 * Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100,
 *              excluding 11,22,33,44,55,66,77,88,99
 */

#include <vector>
#include <cmath>

using namespace std;

// 套数位 dp
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0) return 1;
        vector<int> digits(n, 9);

        vector<vector<int>> dp(n, vector<int>((1 << 10) - 1, -1));
        int state = 0;
        int ans = getdp(n - 1, 1, 1, digits, state, dp);
        return ans;
    }

private:
    using ll = long long;

    int getdp(int pos, int lim, int zero, const vector<int>& digits, int& used, vector<vector<int>>& dp)
    {
        if(pos == -1) return 1; // 数字 0
        if(!lim && !zero && dp[pos][used] != -1)
            return dp[pos][used];

        int ans = 0;
        int up = lim ? digits[pos] : 9;
        if(zero)
            ans += getdp(pos - 1, 0, 1, digits, used, dp);
        for(int i = 0; i <= 9; ++i)
        {
            if(i > up) break;
            if(zero && i == 0) continue;
            if(used & (1 << i)) continue;
            used |= (1 << i);
            ans += getdp(pos - 1, lim && i == up, 0, digits, used, dp);
            used &= (~(1 << i));
        }
        if(!lim && !zero) dp[pos][used] = ans;
        return ans;
    }
};
