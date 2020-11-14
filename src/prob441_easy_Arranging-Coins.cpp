// prob441: Arranging Coins

/*
 * https://leetcode-cn.com/problems/arranging-coins/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int arrangeCoins(int n) {
        if(n == 0) return 0;
        int left = 1, right = n;;
        while(left < right)
        {
            int mid = left + (right - left + 1) / 2;
            ll c = check(mid);
            if(n < c)
                right = mid - 1;
            else
                left = mid;
        }
        return left;
    }

private:
    using ll = long long;

    ll check(int k)
    {
        // k 行需要多少枚硬币
        return (k + 1) * (ll)k / 2;
    }
};
