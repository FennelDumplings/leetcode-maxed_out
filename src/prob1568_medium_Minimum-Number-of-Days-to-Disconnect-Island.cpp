// prob1568: Minimum Number of Days to Disconnect Island

/*
 * https://leetcode-cn.com/problems/minimum-number-of-days-to-disconnect-island/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minDays(vector<vector<int>>& grid)
    {

        int n = grid.size(), m = grid[0].size();
        int cnt = connect_cnt(grid);
        if(cnt > 1 || cnt == 0)
            return 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 0)
                    continue;
                grid[i][j] = 0;
                int cnt = connect_cnt(grid);
                if(cnt > 1 || cnt == 0)
                    return 1;
                grid[i][j] = 1;
            }
        return 2;
    }

private:
    int connect_cnt(const vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 0)
                    continue;
                if(visited[i][j])
                    continue;
                dfs(grid, i, j, visited);
                ++cnt;
            }
        return cnt;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void dfs(const vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& visited)
    {
        visited[i][j] = true;
        int n = grid.size(), m = grid[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(visited[x][y])
                continue;
            if(grid[x][y] == 0)
                continue;
            dfs(grid, x, y, visited);
        }
    }
};
