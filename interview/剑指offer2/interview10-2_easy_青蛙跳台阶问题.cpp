// interview10-2: 青蛙跳台阶问题

/*
 * 一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
 *
 * 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 */

class Solution {
public:
    int numWays(int n) {
        // f1 = 1;
        // f2 = 2;
        // f(n) = f(n-1) + f(n-2)
        const int MOD = 1e9+7;
        if(n == 0) return 1;
        if(n == 1) return 1;
        if(n == 2) return 2;
        int f0 = 1;
        int f1 = 2;
        int f = -1;
        for(int i = 3; i <= n; ++i)
        {
            f = (f0 + f1) % MOD;
            f0 = f1;
            f1 = f;
        }
        return f;
    }
};
