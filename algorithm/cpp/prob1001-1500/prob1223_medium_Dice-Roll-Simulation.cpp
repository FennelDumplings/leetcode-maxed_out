// prob1223: Dice Roll Simulation

/*
 * https://leetcode-cn.com/problems/dice-roll-simulation/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        using ll = long long;
        const int MOD = 1e9 + 7;
        int N = 0;
        for(int i: rollMax) N += i;
        vector<vector<int>> D(N, vector<int>(N, 0));
        // rollStart[i] := 点数 i 在 D 中的起始下标
        // 终止下标为 rollStart[i] + rollMax[i] - 1
        vector<int> rollStart(6);
        for(int i = 1; i < 6; ++i)
            rollStart[i] = rollStart[i - 1] + rollMax[i - 1];
        for(int i = 0; i < 6; ++i)
        {
            for(int j = 0; j < 6; ++j)
            {
                if(i == j)
                {
                    int left = rollStart[i];
                    int len = rollMax[i];
                    for(int x = left; x < left + len; ++x)
                    {
                        for(int y = left; y < left + len; ++y)
                        {
                            if(x + 1 == y)
                                D[x][y] = 1;
                        }
                    }
                }
                else
                {
                    int lefti = rollStart[i];
                    int leni = rollMax[i];
                    int leftj = rollStart[j];
                    for(int x = lefti; x < lefti + leni; ++x)
                        D[x][leftj] = 1;
                }
            }
        }
        // dp[x][i] := 当前状态为 x，再抛 i 次，可形成的方案数
        // sum(dp[rollStart[0~5]][n-1])
        // dp[x][0] = 1
        vector<vector<int>> dp(N, vector<int>(n));
        for(int x = 0; x < N; ++x)
            dp[x][0] = 1;
        for(int i = 1; i < n; ++i)
            for(int x = 0; x < N; ++x)
            {
                for(int y = 0; y < N; ++y)
                {
                    if(D[x][y] == 1)
                        dp[x][i] = (dp[x][i] + (ll)dp[y][i - 1]) % MOD;
                }
            }
        int ans = 0;
        for(int k = 0; k < 6; ++k)
            ans = (ans + dp[rollStart[k]][n - 1]) % MOD;
        return ans;
    }
};
