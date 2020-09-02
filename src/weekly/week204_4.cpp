
#include <vector>

using namespace std;

class Solution {
public:
    using ll = long long;

    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1)
            return 0;
        ll ans = solve(nums);
        ans = (ans - 1 + MOD) % MOD;
        return ans;
    }

    ll solve(vector<int>& nums)
    {
        int n = nums.size();
        if(n <= 1)
            return 0;
        // n > 2
        int t = 0;
        for(int i: nums)
            if(i > nums[0])
                ++t;
        // C(n - 1, t)A(t, t)A(j - i - t, j - i - t)
        //ll ans = Lucas((ll)(n - 1), (ll)t, (ll)MOD);
        ll ans = fac((ll)(n - 1), (ll)MOD) / fac((ll)(t - 1), (ll)MOD);
        vector<int> big, small;
        for(int i = 1; i < n; ++i)
        {
            if(nums[i] > nums[0])
                big.push_back(nums[i]);
            else
                small.push_back(nums[i]);
        }
        if(big.size() > 1)
            ans = (ans * solve(big)) % MOD;
        if(small.size() > 1)
            ans = (ans * solve(small)) % MOD;
        return ans;
    }

private:
    const int MOD = 1e9 + 7;

    ll fac(ll a, ll p)
    {
        ll ans = 1;
        for(ll i = 1; i <= a; ++i)
        {
            ans = (ans * i) % p;
        }
        return ans;
    }

    ll exp_mod(ll a, ll b, ll p)
    {
        //快速幂取模
        ll res = 1;
        while(b != 0)
        {
            if(b & 1) res = (res * a) % p;
            a = (a * a) % p;
            b >>= 1;
        }
        return res;
    }

    ll Comb(ll a, ll b, ll p)
    {
        //求组合数C(a,b) % p
        if(a < b)   return 0;
        if(a == b)  return 1;
        if(b > a - b)   b = a - b;

        ll ans = 1, ca = 1, cb = 1;
        for(ll i = 0; i < b; ++i)
        {
            ca = (ca * (a - i)) % p;
            cb = (cb * (b - i)) % p;
        }
        ans = (ca * exp_mod(cb, p - 2, p)) % p;
        return ans;
    }

    ll Lucas(ll n, ll m, ll p)
    {
        //Lucas定理求C(n,m)%p
        ll ans = 1;

        while(n && m && ans)
        {
            ans = (ans * Comb(n % p, m % p, p)) % p;
            n /= p;
            m /= p;
        }
        return ans;
    }
};

