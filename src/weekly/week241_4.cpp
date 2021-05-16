
#include <vector>

using namespace std;

/*
 * dp[i][k] := i 根根子，看见 k 个的方案数
 * dp[0][...] = 0
 * dp[1][1] = 1
 * dp[i][k] = sum(Comb(i - 1, j) * dp[j][k - 1])
 *     j 为最高棍子左侧的棍子数
 *     i - 1 - j 为最高棍子右侧的棍子数
 */

using ll = long long;
const int MOD = 1e9 + 7;

class C
{
public:
    C(){}
    C(ll n, ll p)
    {
        preprocess(n, p);
    }

    ll operator()(ll n, ll m, ll p) const
    {
        // 先求 $n! \mod p$
        ll ans1 = jc[n];
        // 再求 $m!(n-m)! \mod p$ 的逆元
        ll ans2 = (jc_inv[n][m] * jc_inv[n][n - m]) % p;
        // 再乘起来
        return (ans1 * ans2) % p;
    }

private:
    vector<ll> jc;
    vector<vector<ll>> jc_inv;

    void preprocess(ll n, ll p)
    {
        // jc[i] = i! % p
        jc = vector<ll>(n + 1, 1);
        for(ll i = 1; i <= n; ++i)
            jc[i] = (jc[i - 1] * i) % p;
        jc_inv = vector<vector<ll>>(n + 1, vector<ll>(n + 1, 1));
        // 0 不存在逆元
        for(int N = 1; N <= n; ++N)
            for(ll i = 1; i <= N; ++i)
                jc_inv[N][i] = inv(jc[i], p);
    }

    // 扩展欧几里得求 ax + by = gcd(a, b)
    ll exgcd(ll a, ll b, ll& x, ll& y)
    {
        // 求出 ax + by = gcd(a, b) 的一组特接并返回 a,b 的最大公约数 d。
        if(b == 0)
        {
            x = 1;
            y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, x, y);
        int z = x;
        x = y;
        y = z - y * (a / b);
        return d;
    }

    // 求 b 模 p 的乘法逆元 (b 与 p 互质)
    ll inv(ll b, ll p)
    {
        // 解方程 bx 与 1 模 p 同余
        // 扩展欧几里得求 bx0 + py0 = 1
        ll x0 = 0, y0 = 0;
        ll d = exgcd(b, p, x0, y0);
        if(d != 1) // b 和 p 不互质的情况不不存在逆元
            return -1;
        return (x0 % p + p) % p;
    }
};

class Solution {
public:
    int rearrangeSticks(int n, int K) {
        fac = vector<int>(n, 1);
        fac[0] = 1;
        for(int i = 1; i < n; ++i)
            fac[i] = (fac[i - 1] * (ll)i) % MOD;

        // comb = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
        // for(int i = 0; i <= n; ++i)
        //     comb[i][0] = 1;
        // for(int i = 1; i <= n; ++i)
        //     for(int j = 1; j <= min(i, n); ++j)
        //         comb[i][j] = (comb[i - 1][j] + (ll)comb[i - 1][j - 1]) % MOD;
        c = C(n, MOD);

        dp = vector<vector<int>>(n + 1, vector<int>(K + 1, -1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i)
        {
            dp[i][0] = 0;
            dp[i][1] = fac[i - 1];
        }
        return solve(n, K);
    }

private:
    vector<vector<int>> dp;
    // vector<vector<int>> comb;
    C c;
    vector<int> fac;

    int solve(int n, int K)
    {
        if(dp[n][K] != -1)
            return dp[n][K];
        if(K > n)
            return dp[n][K] = 0;
        // 1 <= K <= n
        dp[n][K] = 0;
        for(int j = K - 1; j <= n - 1; ++j)
        {
            // j: 最高棍子左侧的棍子数
            // n - 1 - j: 最高棍子右侧的棍子数
            // dp[n][K] = ((ll)dp[n][K] + comb[n - 1][j] * (ll)solve(j, K - 1) * fac[n - 1 - j]) % MOD;
            dp[n][K] = ((ll)dp[n][K] + (((ll)c(n - 1, j, MOD) * (ll)solve(j, K - 1)) % MOD) * fac[n - 1 - j]) % MOD;
        }
        return dp[n][K];
    }
};
