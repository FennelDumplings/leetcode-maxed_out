// 4. 给房子涂色 III

/*
 * 在一个小城市里，有 m 个房子排成一排，你需要给每个房子涂上 n 种颜色之一（颜色编号为 1 到 n ）。有的房子去年夏天已经涂过颜色了，所以这些房子不需要被重新涂色。
 *
 * 我们将连续相同颜色尽可能多的房子称为一个街区。（比方说 houses = [1,2,2,3,3,2,1,1] ，它包含 5 个街区  [{1}, {2,2}, {3,3}, {2}, {1,1}]。）
 *
 * 给你一个数组 houses ，一个 m * n 的矩阵 cost 和一个整数 target ，其中：
 *
 * houses[i]：是第 i 个房子的颜色，0 表示这个房子还没有被涂色。
 * cost[i][j]：是将第 i 个房子涂成颜色 j+1 的花费。
 * 请你返回最小总花费，使得每个房子都被涂色后，恰好组成 target 个街区，如果没有涂色方案，请返回 -1 。
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        vector<vector<vector<int> > > dp(m, vector<vector<int> >(n + 1, vector<int>(target + 1, -2)));
        for(int k = 1; k <= n; ++k)
            solve(houses, cost, dp, m - 1, target, n);
        int result = INT_MAX;
        for(int k = 1; k <= n; ++k)
            if(dp[m - 1][k][target] != -1)
                result = min(result, dp[m - 1][k][target]);
        if(result == INT_MAX)
            return -1;
        return result;
    }

private:
    void solve(const vector<int>& houses, const vector<vector<int>>& cost, vector<vector<vector<int> > >& dp, int i, int t, int n)
    {
        // dp[i][k][t] := [0..i] 上，第 i 个涂 k 色，共 t 个街区的涂法
        if(dp[i][1][t] != -2)
            return;

        if(i + 1 < t)
        {
            for(int k = 1; k <= n; ++k)
                dp[i][k][t] = -1;
            return;
        }

        // t <= i + 1
        if(i == 0)
        {
            if(houses[i] != 0)
            {
                // 不需要涂色
                for(int k = 1; k <= n; ++k)
                {
                    if(houses[i] != k)
                        dp[i][k][t] = -1;
                    else
                        dp[i][k][t] = 0;
                }
            }
            else
            {
                // 需要涂色
                for(int k = 1; k <= n; ++k)
                    dp[i][k][t] = cost[i][k - 1];
            }
            return;
        }

        // t <= i + 1
        // i >= 1
        if(t == 1)
        {
            solve(houses, cost, dp, i - 1, t, n);
            if(houses[i] != 0)
            {
                // 不涂色
                for(int k = 1; k <= n; ++k)
                {
                    // 当前色为 k，i - 1 也必须是 k 色，不用枚举 i - 1 位置颜色
                    if(houses[i] != k)
                        dp[i][k][t] = -1;
                    else
                        dp[i][k][t] = dp[i - 1][k][t];
                }
            }
            else
            {
                // 涂色
                for(int k = 1; k <= n; ++k)
                {
                    // 当前色为 k，i - 1 也必须是 k 色，不用枚举 i - 1 位置yanse
                    // dp[i - 1][k][t]
                    if(dp[i - 1][k][t] == -1)
                        dp[i][k][t] = -1;
                    else
                        dp[i][k][t] = dp[i - 1][k][t] + cost[i][k - 1];
                }
            }
            return;
        }

        // t >= i + 1
        // i >= 1
        // t >= 2
        solve(houses, cost, dp, i - 1, t, n);
        solve(houses, cost, dp, i - 1, t - 1, n);
        if(houses[i] != 0)
        {
            // 不涂色
            for(int k = 1; k <= n; ++k)
            {
                // dp[i - 1][k][t] 同色
                // dp[i - 1][k][t - 1] 不同色
                if(houses[i] != k)
                {
                    dp[i][k][t] = -1;
                    continue;
                }
                dp[i][k][t] = INT_MAX;
                for(int kk = 1; kk <= n; ++kk)
                {
                    // 枚举 i - 1 位置的颜色
                    if(kk != k)
                    {
                        // 从 t - 1 转移
                        if(dp[i - 1][kk][t - 1] == -1)
                            continue;
                        dp[i][k][t] = min(dp[i][k][t], dp[i - 1][kk][t - 1]);
                    }
                    else
                    {
                        if(dp[i - 1][kk][t] == -1)
                            continue;
                        // 从 t 转移
                        dp[i][k][t] = min(dp[i][k][t], dp[i - 1][kk][t]);
                    }
                }
                if(dp[i][k][t] == INT_MAX)
                    dp[i][k][t] = -1;
            }
        }
        else
        {
            // 涂色
            for(int k = 1; k <= n; ++k)
            {
                // dp[i - 1][k][t] 同色
                // dp[i - 1][k][t - 1] 不同色
                dp[i][k][t] = INT_MAX;
                for(int kk = 1; kk <= n; ++kk)
                {
                    // 枚举 i - 1 位置的颜色
                    if(kk != k)
                    {
                        // 从 t - 1 转移
                        if(dp[i - 1][kk][t - 1] == -1)
                            continue;
                        dp[i][k][t] = min(dp[i][k][t], cost[i][k - 1] + dp[i - 1][kk][t - 1]);
                    }
                    else
                    {
                        if(dp[i - 1][kk][t] == -1)
                            continue;
                        // 从 t 转移
                        dp[i][k][t] = min(dp[i][k][t], cost[i][k - 1] + dp[i - 1][kk][t]);
                    }
                }
                if(dp[i][k][t] == INT_MAX)
                    dp[i][k][t] = -1;
            }
        }
    }
};
