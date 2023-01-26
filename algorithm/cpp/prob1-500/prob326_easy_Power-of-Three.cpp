// prob326: Power of Three

/*
 * Given an integer, write a function to determine if it is a power of three.
 */

/*
 * Example 1:
 * Input: 27
 * Output: true
 * Example 2:
 * Input: 0
 * Output: false
 * Example 3:
 * Input: 9
 * Output: true
 * Example 4:
 * Input: 45
 * Output: false
 */

/*
 * Follow up:
 * Could you do it without using any loop / recursion?
 */

#include <cmath>

using namespace std;

// 循环迭代
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n <= 0) return false;

        int b = 3;
        while(n % b == 0)
            n /= b;
        return n == 1;
    }
};

// log
class Solution_2 {
public:
    bool isPowerOfThree(int n) {
        if(n <= 0) return false;

        int b = 3;
        double epsilon = 1e-10; // 取 1e-10 可过
        double a = log2(n) / log2(b);
        return (a + epsilon - (int)(a + epsilon)) <= 2 * epsilon;
    }
};
