// prob1463: Cherry Pickup II

/*
 * https://leetcode-cn.com/problems/cherry-pickup-ii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        // dp[i][j1][j2] = (i, j1), (i, j2) 为起点可取的最大
        dp = vector<vector<vector<int>>>(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
        return solve(grid, 0, 0, cols - 1);
    }

private:
    vector<vector<vector<int>>> dp;
    int d_col[3] = {-1, 0, 1};

    int solve(const vector<vector<int>>& grid, int i, int j1, int j2)
    {
        if(dp[i][j1][j2] != -1)
            return dp[i][j1][j2];
        int rows = grid.size(), cols = grid[0].size();
        dp[i][j1][j2] = 0;
        int cur = grid[i][j1];
        if(j2 != j1)
            cur += grid[i][j2];
        if(i == rows - 1)
            return dp[i][j1][j2] = cur;
        for(int d1 = 0; d1 < 3; ++d1)
            for(int d2 = 0; d2 < 3; ++d2)
            {
                if(j1 + d_col[d1] < 0 || j1 + d_col[d1] >= cols)
                    continue;
                if(j2 + d_col[d2] < 0 || j2 + d_col[d2] >= cols)
                    continue;
                dp[i][j1][j2] = max(dp[i][j1][j2], cur + solve(grid, i + 1, j1 + d_col[d1], j2 + d_col[d2]));
            }
        return dp[i][j1][j2];
    }
};
