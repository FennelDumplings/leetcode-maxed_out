// prob1066: Campus Bikes II

/*
 * https://leetcode-cn.com/problems/campus-bikes-ii/
 */

#include <vector>
#include <cmath>
#include <climits>

using namespace std;

// 1 << (0~(n-1)) 人的状态
// 1 << (n~(n+m-1)) 车的状态
// dp[state] := 人和车的状态为 state 时的最小距离和
// 初始化：dp[state] = INT_MAX
// dp[state | i | j] = min(dist(i, j) + dp[state])  (state >> i & 1) && (state >> j & 1)
// dp[(1 << (n + m)) - 1] 为答案

class Solution {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        maskn = (1 << n) - 1;
        maskm = ((1 << (n + m)) - 1) & (~maskn);
        dp = vector<int>((1 << (m + n)), -1);
        return solve(workers, bikes, (1 << (m + n)) - 1);
    }

private:
    vector<int> dp;
    int maskn, maskm;

    int solve(vector<vector<int>>& workers, vector<vector<int>>& bikes, int state)
    {
        if(dp[state] != -1)
            return dp[state];
        if((state & maskn) == 0 || (state & maskm) == 0)
            return dp[state] = 0;
        int n = workers.size(), m = bikes.size();
        dp[state] = INT_MAX / 2;
        for(int i = 0; i < n; ++i)
        {
            if((state >> i & 1) == 0)
                continue;
            for(int j = 0; j < m; ++j)
            {
                if((state >> (n + j) & 1) == 0)
                    continue;
                int d = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
                int prev_state = state & (~(1 << i)) & (~(1 << (n + j)));
                dp[state] = min(dp[state], d + solve(workers, bikes, prev_state));
            }
        }
        return dp[state];
    }
};

class Solution_2 {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        vector<int> dp((1 << (m + n)), INT_MAX / 2);
        dp[0] = 0;
        for(int state = 0; state < (1 << (n + m)); ++state)
        {
            if(dp[state] == INT_MAX / 2)
                dp[state] = 0;
            for(int i = 0; i < n; ++i)
            {
                if((state >> i & 1) == 1)
                    continue;
                for(int j = 0; j < m; ++j)
                {
                    if((state >> (n + j) & 1) == 1)
                        continue;
                    int d = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
                    int nxt_state = state | (1 << i) | (1 << (n + j));
                    dp[nxt_state] = min(dp[nxt_state], dp[state] + d);
                }
            }
        }
        return dp[(1 << (n + m)) - 1];
    }
};
