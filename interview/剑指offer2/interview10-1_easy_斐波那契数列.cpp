// interview10-1: 斐波那契数列

/*
 * 写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。斐波那契数列的定义如下：
 *
 * F(0) = 0,   F(1) = 1
 * F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
 * 斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。
 *
 * 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 */

class Solution {
public:
    // f[0] = 0
    // f[1] = 1;
    // f[n] = f[n-1] + f[n-2]
    // 第 n 项：f[n-1]
    int fib(int n) {
        const int MOD = 1e9 + 7;
        if(n == 0) return 0;
        if(n == 1) return 1;
        int f0 = 0;
        int f1 = 1;
        int f = 0;
        for(int i = 2; i <= n; ++i)
        {
            f = (f0 + f1) % MOD;
            f0 = f1;
            f1 = f;
        }
        return f;
    }
};
