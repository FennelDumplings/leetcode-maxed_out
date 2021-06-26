// prob903: Valid Permutations for DI Sequence

/*
 * https://leetcode-cn.com/problems/valid-permutations-for-di-sequence/
 */

#include <vector>
#include <string>

using namespace std;

// dp[i][j] := 已选 p[0]..p[i] 且未选元素中比 p[i] 小的有 j 个
class Solution_3 {
public:
    int numPermsDISequence(string S) {
        int n = S.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        for(int j = 0; j <= n; ++j)
            dp[0][j] = 1;

        for(int i = 1; i <= n; ++i)
            for(int j = 0; j <= i; ++j)
            {
                if(S[i - 1] == 'D')
                {
                    for(int k = j; k < i; ++k)
                    {
                        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                    }
                }
                else
                {
                    for(int k = 0; k < j; ++k)
                    {
                        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                    }
                }
            }

        int ans = 0;
        for(int x: dp[n])
            ans = (ans + x) % MOD;
        return ans;
    }

private:
    const int MOD = 1e9 + 7;
};


// dp[i][j] := 已选 p[0]..p[i] 且未选元素中比 p[i] 小的有 j 个
// 优化
class Solution_2 {
public:
    int numPermsDISequence(string S) {
        int n = S.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        for(int j = 0; j <= n; ++j)
            dp[0][j] = 1;

        for(int i = 1; i <= n; ++i)
            if(S[i - 1] == 'D')
            {
                for(int j = i - 1; j >= 0; --j)
                {
                    dp[i][j] = (dp[i][j + 1] + dp[i - 1][j]) % MOD;
                }
            }
            else
            {
                for(int j = 1; j <= i; ++j)
                {
                    dp[i][j] = (dp[i][j - 1] + dp[i - 1][j - 1]) % MOD;
                }
            }

        int ans = 0;
        for(int x: dp[n])
            ans = (ans + x) % MOD;
        return ans;
    }

private:
    const int MOD = 1e9 + 7;
};

// 区间DP
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
    int numPermsDISequence(string S) {
        int n = S.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        // dp[0][n]
        // dp[i][j] 对应 S[i..j-1]
        for(int i = 0; i <= n; ++i)
        {
            dp[i][i] = 1;
            // d[i][i] 对应一个数
            if(i < n)
                dp[i][i + 1] = 1;
            // dp[i][i+1] 对应 S[i] 和两个数
        }
        C c(n + 1, MOD);
        for(int len = 3; len <= n + 1; ++len)
            for(int i = 0; i <= n - len + 1; ++i)
            {
                int j = i + len - 1;
                // j - i + 1 = len 个数
                // 对应 j - i 个 DI 序列符号 S[i..j-1]
                if(S[i] == 'I')
                    dp[i][j] = (dp[i][j] + (ll)dp[i + 1][j]) % MOD;
                if(S[j - 1] == 'D')
                    dp[i][j] = (dp[i][j] + (ll)dp[i][j - 1]) % MOD;
                for(int k = i + 1; k <= j - 1; ++k)
                {
                    // k + 1 <= j - 1
                    if(S[k - 1] == 'D' && S[k] == 'I')
                        dp[i][j] = (dp[i][j] + (c(len - 1, k - i, MOD) * (ll)dp[i][k - 1]) % MOD * (ll)dp[k + 1][j]) % MOD;
                }
            }
        return dp[0][n];
    }
};
