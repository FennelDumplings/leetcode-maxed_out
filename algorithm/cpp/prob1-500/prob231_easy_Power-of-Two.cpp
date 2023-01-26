// prob231: Power of Two

/*
 * Given an integer, write a function to determine if it is a power of two.
 */

/*
 * Example 1:
 * Input: 1
 * Output: true
 * Explanation: 20 = 1
 * Example 2:
 * Input: 16
 * Output: true
 * Explanation: 24 = 16
 * Example 3:
 * Input: 218
 * Output: false
 */

// int范围([-2^31, 2^31 -1]) 最大的2的正整数次幂是2^30(1 << 30)
// 如果 2^30 模n余0，说明n 里只有因子2
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && ((1 << 30) % n == 0);
    }
};

// n & (-n) 是 n 中最右边的 1
class Solution_2 {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && ((n & (-n)) == n);
    }
};
