// prob1067: Digit Count in Range

/*
 * Given an integer d between 0 and 9, and two positive integers low and high as lower and upper bounds, respectively. Return the number of times that d occurs as a digit in all integers between low and high, including the bounds low and high.
 */

/*
 * Example 1:
 * Input: d = 1, low = 1, high = 13
 * Output: 6
 * Explanation:
 * The digit d=1 occurs 6 times in 1,10,11,12,13. Note that the digit d=1 occurs twice in the number 11.
 * Example 2:
 * Input: d = 3, low = 100, high = 250
 * Output: 35
 * Explanation:
 * The digit d=3 occurs 35 times in 103,113,123,130,131,...,238,239,243.
 */

/*
 * Note:
 * 0 <= d <= 9
 * 1 <= low <= high <= 2×10^8
 */

#include <vector>

using namespace std;

class Solution {
public:
    int digitsCount(int d, int low, int high) {
        return solve(high, d) - solve(low - 1, d);
    }

private:
    int solve(int N, int d)
    {
        if(N == 0) return 0;
        vector<int> digits;
        while(N)
        {
            digits.push_back(N % 10);
            N /= 10;
        }
        int m = digits.size();
        vector<vector<int>> dp(m, vector<int>(m, -1)); // dp[pos][state]
        int ans = getdp(m - 1, 1, 1, digits, 0, dp, d);
        return ans;
    }

    int getdp(int pos, int lim, int zero, const vector<int>& digits, int state, vector<vector<int>>& dp, int d)
    {
        if(pos == -1) return state;
        if(!lim && !zero && dp[pos][state] != -1)
            return dp[pos][state];
        int ans = 0;
        if(zero)
            ans += getdp(pos - 1, 0, 1, digits, state, dp, d);
        int up = lim ? digits[pos] : 9;
        for(int i = 0; i <= 9; ++i)
        {
            if(i > up)
                break;
            if(zero && i == 0) continue;
            ans += getdp(pos - 1, lim && i == up, 0, digits, state + (i == d), dp, d);
        }
        if(!lim && !zero)
            dp[pos][state] = ans;
        return ans;
    }
};
