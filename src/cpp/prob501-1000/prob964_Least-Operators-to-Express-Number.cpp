// prob964: Least Operators to Express Number

/*
 * https://leetcode-cn.com/problems/least-operators-to-express-number/
 */

#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        int n = log2(target) / log2(x);
        vector<int> cost(n + 2, 0);
        // cost[i] := x^i 连同前面的 +- 的运算符个数
        cost[0] = 2;
        for(int i = 1; i <= n + 1; ++i)
            cost[i] = i;
        unordered_map<int, int> dp;
        // dp[t] := 生成 t 的最小代价(含第一个x前的+-)
        // dp[t] - 1 为答案
        // dp0 = cost[i] + dp[t - x^i]
        // dp1 = cost[i + 1] + dp[x^(i+1) - t]   当 x^(i+1) - t < t 是才考虑这项
        // dp[t] = min(dp0, dp1)
        return solve(target, x, cost, dp) - 1;
    }

private:
    int solve(int t, const int x, const vector<int>& cost, unordered_map<int, int>& dp)
    {
        // if(dp.count(t) > 0)
            // return dp[t];

        int i = log2(t) / log2(x);
        if(pow(x, i) == t)
            return dp[t] = cost[i];

        int dp0 = cost[i] + solve(t - pow(x, i), x, cost, dp);
        dp[t] = dp0;
        if(pow(x, i + 1) - t < t)
        {
            int dp1 = cost[i + 1] + solve(pow(x, i + 1) - t, x, cost, dp);
            dp[t] = min(dp0, dp1);
        }
        return dp[t];
    }
};

// 别人的，没看懂
class Solution_2 {
public:
    int leastOpsExpressTarget(int x, int target)
    {
        vector<int> res;
        while (target)
        {
            res.push_back(target % x);
            target /= x;
        }
        int n = res.size();
        vector<int> l(n), r(n);
        l[0] = res[0] * 2;
        r[0] = (x - res[0]) * 2;
        for (int i = 1; i < n; i++)
        {
            l[i] = min(i * res[i] + l[i - 1], i * (res[i] + 1) + r[i - 1]);
            r[i] = min(i * (x - res[i]) + l[i - 1], i * (x - res[i] - 1) + r[i - 1]);
        }
        return min(l[n - 1], r[n - 1] + n) - 1;
    }
};
