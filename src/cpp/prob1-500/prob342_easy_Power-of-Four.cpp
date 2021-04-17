// prob342: Power of Four

/*
 * Given an integer (signed 32 bits), write a function to check whether it is a power of 4.
 */

/*
 * Example 1:
 * Input: 16
 * Output: true
 * Example 2:
 * Input: 5
 * Output: false
 */

/*
 * Follow up: Could you solve it without loops/recursion?
 */

#include <cmath>

using namespace std;

class Solution {
public:
    bool isPowerOfFour(int num) {
        if (num <= 0) return false;
        int t = sqrt(num);
        return t * t == num && ((1 << 30) % num) == 0;
    }
};

class Solution_2 {
public:
    bool isPowerOfFour(int num) {
        if (num <= 0) return false;
        double epsilon = 1e-10;
        double a = log2(num) / log2(4);
        return (a - (int)a) <= epsilon;
    }
};

class Solution_3 {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && ((num & (-num)) == num) && (num & 0xaaaaaaaa) == 0;
    }
};

class Solution_4 {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && ((num & (-num)) == num) && num % 3 == 1;
    }
};

