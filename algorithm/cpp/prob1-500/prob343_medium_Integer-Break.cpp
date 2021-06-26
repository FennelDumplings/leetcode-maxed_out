// prob343: Integer Break

/*
 *
 * Given a positive integer n, break it into the sum of at least two positive integers and
 * maximize the product of those integers. Return the maximum product you can get.
 */

/*
 * Example 1:
 * Input: 2
 * Output: 1
 * Explanation: 2 = 1 + 1, 1 × 1 = 1.
 * Example 2:
 * Input: 10
 * Output: 36
 * Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
 */

class Solution {
public:
    int integerBreak(int n) {
        if(n <= 3) return 1 * (n - 1);
        int result = 1;
        if(n % 3 == 1)
        {
            result = 4;
            n -= 4;
        }
        else if(n % 3 == 2)
        {
            result = 2;
            n -= 2;
        }

        while(n)
        {
            result *= 3;
            n -= 3;
        }
        return result;
    }
};
