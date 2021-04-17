// prob62: Unique Paths

/*
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 *
 * The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 *
 * How many possible unique paths are there?
 */

/*
 * Example 1:
 * Input: m = 3, n = 2
 * Output: 3
 * Example 2:
 * Input: m = 7, n = 3
 * Output: 28
 */

/*
 * Constraints:
 * 1 <= m, n <= 100
 * It's guaranteed that the answer will be less than or equal to 2 * 10 ^ 9.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int> > dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(i > 0) dp[i][j] += dp[i - 1][j];
                if(j > 0) dp[i][j] += dp[i][j - 1];
            }
        return dp[m - 1][n - 1];
    }
};


class Solution_2 {
public:
    int uniquePaths(int m, int n) {
        return C(n + m - 2, n - 1);
    }

private:
    using ll = long long;
    int C(int n, int m)
    {
        // 调用方保证 n >= m
        if(m > n - m)
            return C(n, n - m);
        vector<vector<ll>> c(n + 1, vector<ll>(m + 1, (ll)0));
        for(int i = 0; i <= n; ++i)
            c[i][0] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= min(i, m); ++j)
            {
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
            }
        return c[n][m];
    }
};

#include <cmath>

class Solution_3 {
public:
    int uniquePaths(int m, int n) {
        return C(n + m - 2, n - 1);
    }

private:
    using ll = long long;

    long double lnC(int n, int m)
    {
        if (m > n)
        {
            return 0;
        }
        if (m * 2 < n)
        {
            m = n - m;
        }
        long double s1 = 0;
        for (int i = m + 1; i <= n; ++i)
        {
            s1 += log((long double)i);
        }
        long double s2 = 0;
        int ub = n - m;
        for (int i = 2; i <= ub; ++i)
        {
            s2 += log((long double)i);
        }
        return s1 - s2;
    }

    ll C(int n, int m)
    {
        if (m > n)
        {
            return 0;
        }
        return round(exp(lnC(n, m)));
    }
};

// -----------------------------------------------------------------------

using ll = long long;

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

// 求 n! mod p
ll fac(ll n, ll p)
{
    if(n == 0)
        return 1;
    ll ans = 1;
    for(int i = 1; i <= n; ++i)
        ans = (ans * i) % p;
    return ans;
}

ll C(ll n, ll m, ll p)
{
    if(m == 0) return 1;
    // 先求 $n! \mod p$
    ll ans1 = fac(n, p);
    // 再求 $m!(n-m)! \mod p$ 的逆元
    ll ans2 = (fac(m, p) * fac(n - m, p)) % p;
    ans2 = inv(ans2, p);
    // 再乘起来
    return (ans1 * ans2) % p;
}

// INT 范围最大的质数 2147483629
class Solution_4 {
public:
    int uniquePaths(int m, int n) {
        const ll MOD = 2147483629;
        return C(n + m - 2, n - 1, MOD);
    }
};

// ----- 预处理

using ll = long long;

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
    ll z = x;
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

// INT 范围最大的质数 2147483629
class Solution {
public:
    int uniquePaths(int m, int n) {
        const ll MOD = 2147483629;
        preprocess(n + m - 2, MOD);
        return C(n + m - 2, n - 1, MOD);
    }

private:
    vector<ll> jc;
    vector<ll> jc_inv;

    void preprocess(ll n, ll p)
    {
        // jc[i] = i! % p
        jc = vector<ll>(n + 1, 1);
        for(ll i = 1; i <= n; ++i)
            jc[i] = (jc[i - 1] * i) % p;
        jc_inv = vector<ll>(n + 1, 1);
        // 0 不存在逆元
        for(ll i = 1; i <= n; ++i)
            jc_inv[i] = inv(jc[i], p);
    }

    ll C(ll n, ll m, ll p)
    {
        if(m == 0) return 1;
        // 先求 $n! \mod p$
        ll ans1 = jc[n];
        // 再求 $m!(n-m)! \mod p$ 的逆元
        ll ans2 = (jc_inv[m] * jc_inv[n - m]) % p;
        // 再乘起来
        return (ans1 * ans2) % p;
    }
};

// 大数
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <climits>

using ll = long long;

struct BigInteger
{
    static const int BASE = 10;
    static const int WIDTH = 1;
    // s 保存大整数各个数位
    // 原数 1234 => s=[4,3,2,1]
    // 进制数为 BASE
    // s[i] 中保存的位数
    vector<int> s;

    // 基本功能
    void show()
    {
        for(int i: s) cout << i << " ";
        cout << endl;
    }

    // 去掉大数的前导0
    void clean()
    {
        while(!s.empty() && s.back() == 0)
            s.pop_back();
    }

    BigInteger(ll num = 0) // 构造函数
    {
        *this = num;
    }

    BigInteger operator=(ll num) // 赋值运算符
    {
        s.clear();
        do
        {
            s.push_back(num % BASE);
            num /= BASE;
        }while(num > 0);
        return *this;
    }

    BigInteger operator=(const string& str) // 赋值运算符
    {
        s.clear();
        int len = (str.length() - 1) / WIDTH + 1;
        int x;
        for(int i = 0; i < len; ++i)
        {
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }

    // 加减乘
    BigInteger operator+(const BigInteger& b) const;
    BigInteger operator-(const BigInteger& b) const;
    BigInteger operator*(const BigInteger& b) const;
    BigInteger operator+=(const BigInteger& b)    // +=运算符
    {
        *this = *this + b;
        return *this;
    }
    BigInteger operator-=(const BigInteger& b)    // -=运算符
    {
        *this = *this - b;
        return *this;
    }
    BigInteger operator*=(const BigInteger& b)    // *=运算符
    {
        *this = *this * b;
        return *this;
    }

    // 大数对小数除法和取模
    BigInteger operator/(const ll& b) const
    {
        // 大数除小数
        BigInteger c;
        c.s.clear();
        c.s.assign((int)s.size(), 0);
        int carry = 0; // 高位未除尽的部分
        for(int i = (int)s.size() - 1; i >= 0; --i)
        {
            c.s[i] = (s[i] + carry * BASE) / b;
            carry = s[i] + carry * BASE - c.s[i] * b;
        }
        c.clean();
        return c;
    }
    BigInteger operator%(const ll& b) const
    {
        long long ans = 0, lena = s.size();
        for(int i = lena - 1; i >= 0; --i)
        {
            ans = (ans * BASE + s[i]) % b;
        }
        return ans;
    }
    BigInteger operator/=(const long long& b) // /=运算符
    {
        *this = *this / b;
        return *this;
    }
    BigInteger operator%=(const ll& b) // %=运算符
    {
        *this = *this % b;
        return *this;
    }

    // 大数对大数除法和取模
    BigInteger operator/(const BigInteger& b) const;
    BigInteger operator%(const BigInteger& b) const;
    BigInteger operator/=(const BigInteger& b)  // /=运算符
    {
        *this = *this / b;
        return *this;
    }
    BigInteger operator %= (const BigInteger& b)    // %=运算符
    {
        *this = *this % b;
        return *this;
    }

    // 比较
    bool operator < (const BigInteger& b) const    // <运算符
    {
        if(s.size()!=b.s.size()) return s.size()<b.s.size();
        for(int i=s.size()-1;i>=0;i--)
            if(s[i]!=b.s[i]) return s[i]<b.s[i];
        return false;
    }
    bool operator > (const BigInteger& b) const    // >运算符
    {
        return b < *this;
    }
    bool operator <= (const BigInteger& b) const   // <=运算符
    {
        return !(b < *this);
    }
    bool operator >= (const BigInteger& b) const   // >=运算符
    {
        return !(*this < b);
    }
    bool operator != (const BigInteger& b) const   // !=运算符
    {
        return b < *this || *this < b;
    }
    bool operator == (const BigInteger& b) const   // ==运算符
    {
        return !(b < *this) && !(*this < b);
    }
};

ostream& operator<<(ostream& out, const BigInteger& x)
{
    out << x.s.back();
    for(int i = x.s.size() - 2; i >= 0; --i)
    {
        string tmp = to_string(x.s[i]);
        string buf(BigInteger::WIDTH - tmp.size(), 0);
        buf += tmp;
        for(int j = 0; j < (int)buf.size(); ++j)
            out << buf[j];
    }
    return out;
}

istream& operator>>(istream& in, BigInteger& x)
{
    string s;
    if(!(in >> s))
        return in;
    x = s;
    return in;
}


BigInteger BigInteger::operator+(const BigInteger& b) const
{
    BigInteger c;
    c.s.clear();
    int iter = 0;
    int carry = 0;
    while(iter < (int)s.size() || iter < (int)b.s.size() || carry != 0)
    {
        int x = carry;
        if(iter < (int)s.size())
            x += s[iter];
        if(iter < (int)b.s.size())
            x += b.s[iter];
        c.s.push_back(x % BASE);
        carry = x / BASE;
        ++iter;
    }
    return c;
}

BigInteger BigInteger::operator-(const BigInteger& b) const
{
    // 大数减小数
    BigInteger c;
    c.s.clear();
    int iter = 0;
    int carry = 0;
    while(iter < (int)s.size() || iter < (int)b.s.size() || carry != 0)
    {
        int x = carry;
        carry = 0;
        if(iter < (int)s.size())
            x += s[iter];
        if(iter < (int)b.s.size())
            x -= b.s[iter];
        if(x < 0)
        {
            x += BASE;
            carry = -1;
        }
        c.s.push_back(x);
        ++iter;
    }
    c.clean();
    return c;
}

BigInteger BigInteger::operator*(const BigInteger& b) const
{
    BigInteger c;
    int lena = s.size(), lenb = b.s.size(), lenc = lena + lenb;
    c.s.clear();
    c.s.assign(lenc, 0);
    for(int i = 0; i < lena; ++i)
    {
        for(int j = 0; j < lenb; ++j)
        {
            c.s[i + j] += s[i] * b.s[j];
        }
    }
    for(int i = 0; i < lenc - 1; ++i)
    {
        c.s[i + 1] += c.s[i] / BASE;
        c.s[i] %= BASE;
    }
    c.clean();
    return c;
}

BigInteger BigInteger::operator/(const BigInteger& b) const
{
    BigInteger c;
    c.s.clear();
    c.s.assign((int)s.size(), 0);
    BigInteger carry;
    carry = 0; // 高位未除尽的部分
    for(int i = (int)s.size() - 1; i >= 0; --i)
    {
        carry = carry * BASE + s[i];
        int j = 0;
        // 求 b * j <= carry 的最大 j
        while(j < BASE)
        {
            if(carry < b * (j + 1))
                break;
            ++j;
        }
        c.s[i] = j;
        carry = carry - b * j;
    }
    c.clean();
    return c;
}

BigInteger BigInteger::operator%(const BigInteger& b) const
{
    BigInteger carry = 0;
    for(int i = (int)s.size() - 1; i >= 0; --i)
    {
        carry = carry * BASE + s[i];
        int j = 0;
        while(j < BASE)
        {
            if(carry < b * (j + 1))
                break;
            ++j;
        }
        carry = carry - b * j;
    }
    return carry;
}

BigInteger fac(BigInteger n)
{
    if(n == 0)
        return 1;
    BigInteger ans = 1;
    for(BigInteger i = 1; i <= n; i += 1)
        ans = (ans * i);
    return ans;
}

BigInteger C(BigInteger n, BigInteger m)
{
    if(m == 0) return 1;
    BigInteger ans1 = fac(n);
    BigInteger ans2 = (fac(m) * fac(n - m));
    return ans1 / ans2;
}


class Solution {
public:
    int uniquePaths(int m, int n) {
        BigInteger ans_big = C(n + m - 2, n - 1);
        stringstream ss;
        ss << ans_big;
        int ans_int;
        ss >> ans_int;
        return ans_int;
    }
};
