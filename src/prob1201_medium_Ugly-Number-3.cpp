// prob1201: Ugly Number III

/*
 * https://leetcode-cn.com/problems/ugly-number-iii/
 */

#include <climits>
#include <numeric>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        int left = 1;
        int right = INT_MAX;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            int k = check(a, b, c, mid);
            if(k < n)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

private:
    using ll = long long;

    ll gcd(ll a,ll b)
    {
        if(b == 0)
            return a;
        return gcd(b, a % b);
    }

    ll gcd2(ll x, ll y)
    {
        while (y != 0)
        {
          ll t = x % y;
          x = y;
          y = t;
        }
        return x;
    }

    ll lcm(ll x, ll y)
    {
        return (ll)x * y / gcd2(x, y);
    }

    int check(int a, int b, int c, int k)
    {
        // <= k 的丑数有多少个
        return k / a + k / b + k / c - k / lcm(a, b) - k / lcm(a, c) - k / lcm(b, c) + k / lcm(lcm(a, b), c);
    }
};
