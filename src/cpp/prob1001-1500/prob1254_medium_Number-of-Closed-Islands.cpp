// prob1254: Number of Closed Islands

/*
 * https://leetcode-cn.com/problems/number-of-closed-islands/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        visited.assign(n, vector<bool>(m, false));
        int ans = 0;
        for(int i = 1; i < n - 1; ++i)
        {
            for(int j = 1; j < m - 1; ++j)
            {
                if(grid[i][j] == 1)
                    continue;
                if(visited[i][j])
                    continue;
                visited[i][j] = true;
                if(dfs(grid, i, j))
                    ++ans;
            }
        }
        return ans;
    }

private:
    vector<vector<bool>> visited;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    bool dfs(const vector<vector<int>>& grid, int i, int j)
    {
        int n = grid.size(), m = grid[0].size();
        bool flag = true;
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
            {
                flag = false;
                continue;
            }
            if(grid[x][y] == 1)
                continue;
            if(visited[x][y])
                continue;
            visited[x][y] = true;
            flag = dfs(grid, x, y) && flag;
        }
        return flag;
    }
};


