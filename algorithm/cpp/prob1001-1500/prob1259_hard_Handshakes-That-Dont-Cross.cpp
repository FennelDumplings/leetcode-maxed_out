// prob1259: Handshakes That Don't Cross

/*
 * You are given an even number of people num_people that stand around a circle and each person
 * shakes hands with someone else, so that there are num_people / 2 handshakes total.
 * Return the number of ways these handshakes could occur such that none of the handshakes cross.
 * Since this number could be very big, return the answer mod 10^9 + 7
 */

#include <vector>

using namespace std;

// DP
class Solution {
public:
    int numberOfWays(int num_people) {
        using ll = long long;
        int MOD = 1e9 + 7;
        if(num_people == 0) return 0;
        int n = num_people / 2;
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i <= n; ++i)
        {
            for(int j = 0; j <= i - 1; ++j)
                dp[i] = (dp[i] + (ll)dp[j] * dp[i - 1 - j]) % MOD;
        }
        return dp[n];
    }
};

// 卢卡斯定理模板
// Lucas 定理实现 C(n,m) % p 的代码：
using ll = long long;
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

class Solution_2 {
public:
    int numberOfWays(int num_people) {
        using ll = long long;
        int MOD = 1e9 + 7;
        if(num_people == 0) return 0;
        int n = num_people / 2;
        ll ans = (Lucas((ll)2 * n, n, (ll)MOD) - Lucas((ll)2 * n, (ll)(n - 1), (ll)MOD) + MOD) % MOD;
        return (int)ans;
    }
};
