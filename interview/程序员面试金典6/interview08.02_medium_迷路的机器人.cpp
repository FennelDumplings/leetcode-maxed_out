// interview08.02: 迷路的机器人

/*
 * https://leetcode-cn.com/problems/robot-in-a-grid-lcci/
 */

#include <vector>

using namespace std;

// dfs 不带 visited
// TLE
class Solution {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()) return {};
        if(obstacleGrid[0][0] == 1)
            return {};
        vector<vector<int>> path({{0, 0}});
        bool flag = dfs(obstacleGrid, 0, 0, path);
        if(!flag) return {};
        return path;
    }

private:
    bool dfs(const vector<vector<int>>& grid, int x, int y, vector<vector<int>>& path)
    {
        int n = grid.size(), m = grid[0].size();
        if(x == n - 1 && y == m - 1)
        {
            return true;
        }
        if(x < n - 1 && grid[x + 1][y] == 0)
        {
            path.push_back({x + 1, y});
            if(dfs(grid, x + 1, y, path))
                return true;
            path.pop_back();
        }
        if(y < m - 1 && grid[x][y + 1] == 0)
        {
            path.push_back({x, y + 1});
            if(dfs(grid, x, y + 1, path))
                return true;
            path.pop_back();
        }
        return false;
    }
};

#include <algorithm>

// DP
class Solution_2 {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& grid) {
        if(grid.empty()) return {};
        if(grid[0][0] == 1)
            return {};
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> dp(n, vector<bool>(m, false));
        dp[0][0] = true;
        for(int j = 1; j < m; ++j)
            dp[0][j] = dp[0][j - 1] && grid[0][j] == 0;
        for(int i = 1; i < n; ++i)
            dp[i][0] = dp[i - 1][0] && grid[i][0] == 0;
        for(int i = 1; i < n; ++i)
            for(int j = 1; j < m; ++j)
            {
                if(grid[i][j] == 0)
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        if(!dp[n - 1][m - 1]) return {};
        vector<vector<int>> path;
        int x = n - 1, y = m - 1;
        while(x != 0 || y != 0)
        {
            path.push_back({x, y});
            if(x > 0 && dp[x - 1][y])
                --x;
            else if(y > 0 && dp[x][y - 1])
                --y;
            else
                return {};
        }
        path.push_back({0, 0});
        reverse(path.begin(), path.end());
        return path;
    }
};
