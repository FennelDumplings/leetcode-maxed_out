// prob878: Nth Magical Number

/*
 * https://leetcode-cn.com/problems/nth-magical-number/
 */

#include <climits>
#include <numeric>

using namespace std;

class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {
        ll left = 1, right = LONG_MAX / 2;
        while(left < right)
        {
            ll mid = left + (right - left) / 2;
            ll cnt = check(mid, A, B);
            if(cnt >= N)
                right = mid;
            else
                left = mid + 1;
        }
        return left % MOD;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;

    ll check(ll mid, ll A, ll B)
    {
        // <= mid 的神奇数个数
        return mid / A + mid / B - mid / lcm<ll>(A, B);
    }
};
