// prob829: Consecutive Numbers Sum

/*
 * Given a positive integer N, how many ways can we write it as a sum of consecutive positive integers?
 */

/*
 * Example 1:
 * Input: 5
 * Output: 2
 * Explanation: 5 = 5 = 2 + 3
 * Example 2:
 * Input: 9
 * Output: 3
 * Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4
 * Example 3:
 * Input: 15
 * Output: 4
 * Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
 */

/*
 * Note: 1 <= N <= 10 ^ 9.
 */

class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int res = 0;
        for(int b = 1; b * (b - 1) < 2 * N; ++b)
            if((2 * N) % b == 0 && (2 * N / b - (b - 1)) % 2 == 0)
                ++res;
        return res;
    }
};
