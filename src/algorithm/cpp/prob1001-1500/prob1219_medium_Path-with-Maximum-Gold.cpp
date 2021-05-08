// prob1219: Path with Maximum Gold

/*
 * https://leetcode-cn.com/problems/path-with-maximum-gold/
 */

#include <vector>
#include <unordered_map>

using namespace std;

// 回溯
class Solution_2 {
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int id = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] != 0)
                    mapping[i * m + j] = id++;
            }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] != 0)
                    ans = max(ans, solve(grid, i, j, 0));
            }
        return ans;
    }

private:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    unordered_map<int, int> mapping;

    int solve(vector<vector<int>>& grid, int i, int j, int state)
    {
        // 以 (i, j) 起点，已经选 state 能取到的最大
        int n = grid.size(), m = grid[0].size();
        int mx = 0;
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(grid[x][y] != 0 && (state >> (mapping[x * m + y]) & 1) == 0)
                mx = max(mx, solve(grid, x, y, state | (1 << (mapping[i * m + j]))));
        }
        return mx + grid[i][j];
    }
};


// 优化，不开 visited 管理回溯，而是直接在 grid 上修改
class Solution {
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] != 0)
                    ans = max(ans, solve(grid, i, j));
            }
        return ans;
    }

private:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    int solve(vector<vector<int>>& grid, int i, int j)
    {
        // 以 (i, j) 起点，已经选 state 能取到的最大
        int n = grid.size(), m = grid[0].size();
        int mx = 0;
        int tmp = grid[i][j];
        grid[i][j] = 0;
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(grid[x][y] == 0)
                continue;
            mx = max(mx, solve(grid, x, y));
        }
        grid[i][j] = tmp;
        return mx + grid[i][j];
    }
};

