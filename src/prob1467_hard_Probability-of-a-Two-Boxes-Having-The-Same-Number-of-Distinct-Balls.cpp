// prob1467: Probability of a Two Boxes Having The Same Number of Distinct Balls

/*
 * https://leetcode-cn.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/
 */

#include <vector>

using namespace std;

class Solution {
public:
    double getProbability(vector<int>& balls) {
        int k = balls.size();
        int n = 0;
        for(int i: balls) n += i;
        n /= 2;
        solve(0, 0, 0, 0, balls);
    }

private:
    // dp[i][x][j][y] := 第 1 盒放了 i 个球，持有 x 这些颜色，第 2 盒放了 j 个球，持有 y 这些颜色的方案数
    int dp[25][8][25][8];

    void solve(int i, int x, int j, int y, vector<int> balls)
    {
        // b1 [i..n-1], b2 [j..n-1] 填球，剩余的球为 balls
    }
};
