// prob172: Factorial Trailing Zeroes

/*
 * Given an integer n, return the number of trailing zeroes in n!.
 */

/*
 * Example 1:
 *
 * Input: 3
 * Output: 0
 * Explanation: 3! = 6, no trailing zero.
 * Example 2:
 *
 * Input: 5
 * Output: 1
 * Explanation: 5! = 120, one trailing zero.
 */

/*
 * Note: Your solution should be in logarithmic time complexity.
 */

// n, n-1, n-2, ..., 1 中有多少个 5
class Solution {
public:
    int trailingZeroes(int n) {
        // 31
        // 31 / 5 = 6;
        // 31 / 25 = 1;
        // 31/ 125 = 0;
        // ans = 7
        long long iter = 5;
        long long ans = 0;
        while(n / iter > 0)
        {
            ans += n / iter;
            iter *= 5;
        }
        return ans;
    }
};
