// prob264: Ugly Number

/*
 * Write a program to find the n-th ugly number.
 * Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
 */

/*
 * Example:
 * Input: n = 10
 * Output: 12
 * Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
 */

/*
 * Note:
 * 1 is typically treated as an ugly number.
 * n does not exceed 1690.
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 1;
        int i2 = 1;
        int i3 = 1;
        int i5 = 1;
        for(int i = 2; i <= n; ++i)
        {
            dp[i] = min(dp[i], dp[i2] * 2);
            dp[i] = min(dp[i], dp[i3] * 3);
            dp[i] = min(dp[i], dp[i5] * 5);
            if(dp[i] == dp[i2] * 2) ++i2;
            if(dp[i] == dp[i3] * 3) ++i3;
            if(dp[i] == dp[i5] * 5) ++i5;
        }
        return dp[n];
    }
};
