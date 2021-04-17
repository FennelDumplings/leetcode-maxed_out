// prob741: Cherry Pickup

/*
 * In a N x N grid representing a field of cherries, each cell is one of three possible integers.
 * 0 means the cell is empty, so you can pass through;
 * 1 means the cell contains a cherry, that you can pick up and pass through;
 * -1 means the cell contains a thorn that blocks your way.
 *  Your task is to collect maximum number of cherries possible by following the rules below:
 *  Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
 *  After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
 *  When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
 *  If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
 */

/*
 * Example 1:
 *
 * Input: grid =
 * [[0, 1, -1],
 *  [1, 0, -1],
 *   [1, 1,  1]]
 *   Output: 5
 *   Explanation:
 *   The player started at (0, 0) and went down, down, right right to reach (2, 2).
 *   4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
 *   Then, the player went left, up, up, left to return home, picking up one more cherry.
 *   The total number of cherries picked up is 5, and this is the maximum possible.
 */

/*
 * Note:
 *
 * grid is an N by N 2D array, with 1 <= N <= 50.
 * Each grid[i][j] is an integer in the set {-1, 0, 1}.
 * It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.
 */

#include <vector>

using namespace std;

// 贪心：先去程走最大，然后更新 grid，然后回程走最大
// 答案错
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int> > dp(n, vector<int>(n, -2));
        dp[0][0] = grid[0][0];
        _solve(grid, n - 1, n - 1, dp);
        if(dp[n - 1][n - 1] == -1) return 0;
        int result = dp[n - 1][n - 1];
        grid[n - 1][n - 1] = 0;
        int i = n - 1, j = n - 1;
        while(i > 0 && j > 0)
        {
            if(dp[i - 1][j] >= dp[i][j - 1])
            {
                grid[i - 1][j] = 0;
                --i;
            }
            else
            {
                grid[i][j - 1] = 0;
                --j;
            }
        }
        while(i > 0)
        {
            grid[i - 1][j] = 0;
            --i;
        }
        while(j > 0)
        {
            grid[i][j - 1] = 0;
            --j;
        }
        dp.assign(n, vector<int>(n, -2));
        dp[n - 1][n - 1] = 0;
        for(int i = n - 2; i >= 0; --i)
        {
            if(grid[i][n - 1] == -1 || dp[i + 1][n - 1] == -1)
                dp[i][n - 1] = -1;
            else
                dp[i][n - 1] = grid[i][n - 1] + dp[i + 1][n - 1];
        }
        for(int j = n - 2; j >= 0; --j)
        {
            if(grid[n - 1][n - 1] == -1 || dp[n - 1][j + 1] == -1)
                dp[n - 1][j + 1] = -1;
            else
                dp[n - 1][j] = grid[n - 1][j] + dp[n - 1][j + 1];
        }
        for(int i = n - 2; i >= 0; --i)
            for(int j = n - 2; j >= 0; --j)
            {
                if(grid[i][j] == -1 || (grid[i + 1][j] == -1 && grid[i][j + 1] == -1))
                    dp[i][j] = -1;
                else if(grid[i + 1][j] == -1)
                    dp[i][j] = grid[i][j] + dp[i][j + 1];
                else if(grid[i][j + 1] == -1)
                    dp[i][j] = grid[i][j] + dp[i + 1][j];
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]) + grid[i][j];
            }
        result += dp[0][0];
        return result;
    }

private:
    void _solve(const vector<vector<int> >& grid, int i, int j, vector<vector<int> >& dp)
    {
        if(i == 0 && j == 0)
            return;
        if(dp[i][j] != -2)
            return;

        if(i == 0)
        {
            _solve(grid, i, j - 1, dp);
            if(grid[i][j] == -1 || dp[i][j - 1] == -1)
                dp[i][j] = -1;
            else
                dp[i][j] = grid[i][j] + dp[i][j - 1];
            return;
        }
        if(j == 0)
        {
            _solve(grid, i - 1, j, dp);
            if(grid[i][j] == -1 || grid[i - 1][j] == -1)
                dp[i][j] = -1;
            else
                dp[i][j] = grid[i][j] + grid[i - 1][j];
            return;
        }

        _solve(grid, i, j - 1, dp);
        _solve(grid, i - 1, j, dp);
        if(grid[i][j] == -1 || (grid[i - 1][j] == -1 && grid[i][j - 1] == -1))
            dp[i][j] = -1;
        else if(grid[i - 1][j] == -1)
            dp[i][j] = grid[i][j] + dp[i][j - 1];
        else if(grid[i][j - 1] == -1)
            dp[i][j] = grid[i][j] + dp[i - 1][j];
        else
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
    }
};

// 与其从左上角走到右下角，再从右下角走到左上角；不如直接考虑从左上角选两条路走到右下角。
// https://leetcode-cn.com/problems/cherry-pickup/solution/dong-tai-gui-hua-xiang-xi-jie-xi-tu-jie-by-newhar/
class Solution_2 {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // dp[r1][c1][c2] := (r1, c1), (r2, c2) 到 (N - 1, N - 1) 的最多樱桃数目
        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(m , vector<int>(m, -2)));
        dp[n - 1][m - 1][m - 1] = grid[n - 1][m - 1];
        int ans = solve(0, 0, 0, grid);
        if(ans == -1) return 0;
        return ans;
    }

private:
    vector<vector<vector<int>>> dp;
    int solve(int r1, int c1, int c2, const vector<vector<int>>& grid)
    {
        if(dp[r1][c1][c2] != -2)
            return dp[r1][c1][c2];
        int r2 = c1 + r1 - c2;
        if(grid[r1][c1] == -1 || grid[r2][c2] == -1)
            return dp[r1][c1][c2] = -1;
        int ans = 0;
        if(grid[r1][c1] == 1)
            ++ans;
        if(r1 != r2 && grid[r2][c2] == 1)
            ++ans;
        int max_later = -2;
        int n = grid.size(), m = grid[0].size();
        if(r1 < n - 1 && r2 < n - 1)
            max_later = max(max_later, solve(r1 + 1, c1, c2, grid));
        if(c1 < m - 1 && r2 < n - 1)
            max_later = max(max_later, solve(r1, c1 + 1, c2, grid));
        if(r1 < n - 1 && c2 < m - 1)
            max_later = max(max_later, solve(r1 + 1, c1, c2 + 1, grid));
        if(c1 < m - 1 && c2 < m - 1)
            max_later = max(max_later, solve(r1, c1 + 1, c2 + 1, grid));
        if(max_later < 0)
            dp[r1][c1][c2] = -1;
        else
            dp[r1][c1][c2] = ans + max_later;
        return dp[r1][c1][c2];
    }
};






