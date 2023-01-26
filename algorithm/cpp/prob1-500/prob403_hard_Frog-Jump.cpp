// prob403: Frog Jump

/*
 * A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.
 * Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.
 * If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.
 * Note:
 * The number of stones is ≥ 2 and is < 1,100.
 * Each stone's position will be a non-negative integer < 231.
 * The first stone's position is always 0.
 */

/*
 * Example 1:
 * [0,1,3,5,6,8,12,17]
 * There are a total of 8 stones.
 * The first stone at the 0th unit, second stone at the 1st unit,
 * third stone at the 3rd unit, and so on...
 * The last stone at the 17th unit.
 * Return true. The frog can jump to the last stone by jumping
 * 1 unit to the 2nd stone, then 2 units to the 3rd stone, then
 * 2 units to the 4th stone, then 3 units to the 6th stone,
 * 4 units to the 7th stone, and 5 units to the 8th stone.
 * Example 2:
 * [0,1,2,3,4,8,9,11]
 * Return false. There is no way to jump to the last stone as
 * the gap between the 5th and 6th stone is too large.
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones.empty()) return false;
        int n = stones.size();
        if(n == 1) return true;
        // n >= 2
        // 到不了第二个石头
        if(stones[0] + 1 < stones[1])
            return false;
        for(int i = 1; i < n; ++i)
            mapping[stones[i]] = i;
        // 可以到第二个石头 dp[1][1] := 第二(stones[1])个石头，上一步跳1，能否到达
        vector<vector<int>> dp(n, vector<int>(n, 0)); // dp[i][k] := 当前在第 i 个石子 stone[i], 上一步跳 k 步，能否达到 stone[n - 1]
        for(int k = 0; k < n; ++k)
            dp[n - 1][k] = 1;
        int ans = solve(1, 1, stones, dp);
        return ans == 1;
    }

private:
    unordered_map<int, int> mapping; // 石头 -> 下标

    int solve(int i, int k, const vector<int>& stones, vector<vector<int>>& dp)
    {
        if(dp[i][k] != 0)
            return dp[i][k];

        // 下一步候选
        // stone[i - 1] + k - 1
        // stone[i - 1] + k
        // stone[i - 1] + k + 1
        for(int step = k - 1; step <= k + 1; ++step)
        {
            if(step <= 0) continue;
            int nxt = stones[i] + step;
            if(mapping[nxt] <= i)
                continue;
            solve(mapping[nxt], step, stones, dp);
            if(dp[mapping[nxt]][step] == 1)
            {
                dp[i][k] = 1;
                return 1;
            }
        }
        return dp[i][k] = -1;
    }
};
