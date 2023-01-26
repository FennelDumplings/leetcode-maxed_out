// prob633: Sum of Square Numbers

/*
 * Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.
 */

/*
 * Example 1:
 * Input: 5
 * Output: True
 * Explanation: 1 * 1 + 2 * 2 = 5
 * Example 2:
 * Input: 3
 * Output: False
 */

#include  <cmath>

using namespace std;

// TLE
class Solution {
public:
    bool judgeSquareSum(int c) {
        if(c == 0) return true;
        for(int i = 0; (ll)i * i * 2 <= (ll)c; ++i)
        {
            if(_check(c - i * i))
                return true;
        }
        return false;
    }

private:
    using ll = long long;

    bool _check(int c)
    {
        // 需要二分才行
        if(c == 0) return true;
        for(int i = 1; (ll)i * i <= (ll)c; ++i)
        {
            if(i * i == c)
                return true;
        }
        return false;
    }
};


class Solution_2 {
public:
    bool judgeSquareSum(int c) {
        if(c == 0) return true;
        using ll = long long;
        for(int i = 0; (ll)i * i * 2 <= (ll)c; ++i)
        {
            double r = sqrt(c - i * i);
            if((int)r * (int)r == c - i * i)
                return true;
        }
        return false;
    }
};
