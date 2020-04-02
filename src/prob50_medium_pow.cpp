// prob50: pow

/*
 * Implement pow(x, n), which calculates x raised to the power n (x^n).
 */

/*
 * Example 1:
 * Input: 2.00000, 10
 * Output: 1024.00000
 * Example 2:
 * Input: 2.10000, 3
 * Output: 9.26100
 * Example 3:
 * Input: 2.00000, -2
 * Output: 0.25000
 * Explanation: 2-2 = 1/22 = 1/4 = 0.25
 */

/*
 * Note:
 * -100.0 < x < 100.0
 *  n is a 32-bit signed integer, within the range [−231, 231 − 1]
 */

class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1.0;
        if(n < 0) return 1 / _quickqower(x, -(ll)n);
        return _quickqower(x, n);
    }

private:
    using ll = long long;

    double _quickqower(double x, ll n)
    {
        double ans = 1.0;
        while(n)
        {
            if(n & 1) ans = (ans * x);
            x = x * x;
            n >>= 1;
        }
        return ans;
    }
};

// 递归写法
class Solution_2 {
public:
    double myPow(double x, int n) {
        using ll = long long;
        return _myPow(x, (ll)n);
    }

private:
    double _myPow(double x, long long n) {
        if (n == 0)
            return 1;
        if (n < 0)
            return 1 / _myPow(x, -n);
        double mid = _myPow(x, n / 2);
        if (n & 1)
            return mid * mid * x;
        return mid * mid;
    }
};
