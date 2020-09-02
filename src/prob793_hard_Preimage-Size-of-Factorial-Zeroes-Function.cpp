// prob793: Preimage Size of Factorial Zeroes Function

/*
 * https://leetcode-cn.com/problems/preimage-size-of-factorial-zeroes-function/
 */

#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    int preimageSizeFZF(int K) {
        if(K == 0)
            return 5;
        ll left = (ll)1, right = (ll)5 * K + 1;
        while(left < right)
        {
            ll mid = left + (right - left) / 2;
            int cnt = trailing_zero_cnt(mid);
            if(cnt == K)
                return 5;
            else if(cnt < K)
                left = mid + 1;
            else
                right = mid;
        }
        return 0;
    }

private:
    using ll = long long;

    int trailing_zero_cnt(ll n)
    {
        // N! 结尾 0 的个数
        ll ans = 0;
        if(n < 5) return ans;
        while(n >= 5)
        {
            ans += n / 5;
            n /= 5;
        }
        return ans;
    }
};
