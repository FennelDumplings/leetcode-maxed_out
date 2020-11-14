// prob1510: Stone Game IV

/*
 * https://leetcode-cn.com/problems/stone-game-iv/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        dp[0] = vector<int>(n + 1, -1);
        dp[1] = vector<int>(n + 1, -1);
        dp[0][0] = 0;
        dp[1][0] = 1;
        int ans = solve(n, 0);
        return ans == 1;
    }

private:
    vector<int> dp[2];

    int solve(int i, int k)
    {
        if(dp[k][i] != -1)
            return dp[k][i];
        if(k & 1)
        {
            for(int j = 1; j * j <= i; ++j)
            {
                if(solve(i - j * j, k ^ 1) == 0)
                    return dp[k][i] = 0;
            }
            return dp[k][i] = 1;
        }
        else
        {
            for(int j = 1; j * j <= i; ++j)
            {
                if(solve(i - j * j, k ^ 1) == 1)
                    return dp[k][i] = 1;
            }
            return dp[k][i] = 0;
        }
    }
};
