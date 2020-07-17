// interview16: 数值的整数次方

/*
 * https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/
 */

#include <cmath>

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1.0;
        if(x == 0) return 0.0;
        double ans = _myPow(abs(x), abs((ll)n));
        if(n < 0)
            ans = 1 / ans;
        if(x < 0 && (n & 1))
            ans = -ans;
        return ans;
    }

private:
    using ll = long long;
    double _myPow(double x, ll n) {
        double ans = 1.0;
        while(n)
        {
            if(n & 1)
                ans *= x;
            x *= x;
            n >>= 1;
        }
        return ans;
    }
};
