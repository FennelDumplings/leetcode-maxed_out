// prob906: Super Palindromes

/*
 * https://leetcode-cn.com/problems/super-palindromes/
 */

#include <string>
#include <sstream>
#include <cmath>

using namespace std;

class Solution {
public:
    int superpalindromesInRange(string L_str, string R_str) {
        stringstream ss;
        ss << L_str;
        ss >> L;
        ss.clear();
        ss << R_str;
        ss >> R;

        int l = ceil(sqrt(L));
        int r = floor(sqrt(R));

        int dl = len(l), dr = len(r);
        dl = (dl + 1) / 2, dr = (dr + 1) / 2;
        int ans = 0;
        for(int d = dl; d <= dr; ++d)
            ans += solve(d);
        return ans;
    }

private:
    using ll = long long;
    ll L, R;

    int solve(int l)
    {
        // 11 ~ 99
        int ans = 0;
        for(ll x = pow(10, l - 1); x <= pow(10, l) - 1; ++x)
        {
            ll y1 = x;
            int tmp = x;
            while(tmp)
            {
                y1 *= 10;
                y1 += tmp % 10;
                tmp /= 10;
            }
            if(y1 > R / y1)
                break;
            ll cand1 = y1 * y1;
            if(cand1 >= L && check(cand1))
            {
                ++ans;
            }
        }
        for(ll x = pow(10, l - 1); x <= pow(10, l) - 1; ++x)
        {
            ll y2 = x;
            int tmp = x;
            tmp /= 10;
            while(tmp)
            {
                y2 *= 10;
                y2 += tmp % 10;
                tmp /= 10;
            }
            if(y2 > R / y2)
                break;
            ll cand2 = y2 * y2;
            if(cand2 >= L && check(cand2))
            {
                ++ans;
            }
        }
        return ans;
    }

    bool check(ll x)
    {
        ll y1 = x;
        ll y2 = 0;
        while(x)
        {
            y2 *= 10;
            y2 += x % 10;
            x /= 10;
        }
        return y1 == y2;
    }

    int len(int x)
    {
        int ans = 0;
        while(x)
        {
            x /= 10;
            ++ans;
        }
        return ans;
    }
};
