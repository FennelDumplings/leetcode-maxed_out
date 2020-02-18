// prob7 Reverse Integer

/*
 * Given a 32-bit signed integer, reverse digits of an integer.
 */

/* Examples:
 * Example 1:
 * Input: 123
 * Output: 321
 *
 * Example 2:
 * Input: -123
 * Output: -321
 *
 * Example 3:
 * Input: 120
 * Output: 21
 */

/* Note:
 * Assume we are dealing with an environment which could only store integers within
 * the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem,
 * assume that your function returns 0 when the reversed integer overflows.
 */

#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        if(x == 0) return 0;
        if(x == INT_MIN) return 0;

        int remains = x;
        if(x < 0) remains = -x;

        // 以下是队列的思想
        int iter = 0;
        int result = 0;
        for(; remains > 0; remains /= 10)
        {
            iter = remains % 10;
            if(result > (INT_MAX - iter) / 10)
                return 0;
            result = 10 * result + iter; // 这一步可能溢出
        }

        if(x < 0)
            result = -result;

        return result;

    }
};
