// prob749: Contain Virus

/*
 * https://leetcode-cn.com/problems/contain-virus/
 */

#include <vector>

using namespace std;

struct Point
{
    int x, y;
    Point(int x, int y):x(x),y(y){}
};

class Solution {
public:
    int containVirus(vector<vector<int>>& grid) {
        // 1 感染但尚未隔离区域，0 未感染区域 2 已经隔离区域
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        vector<Point> cc;
        vector<vector<bool>> visited, visited2;

        while(true)
        {
            int max_spread_num = 0; // 与 cc 邻接的区域数量最大值
            int block_num = 0; // cc 的周长最大值
            Point isolate(-1, -1); // 最值的 cc
            cc.clear();
            visited.assign(n, vector<bool>(m, false));
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                {
                    if(grid[i][j] != 1)
                        continue;
                    if(visited[i][j])
                        continue;
                    cc.emplace_back(i, j);
                    int spread_num = 0;
                    int block = 0;
                    visited2.assign(n, vector<bool>(m, false));
                    dfs(grid, visited, visited2, i, j, spread_num, block);
                    if(spread_num > max_spread_num)
                    {
                        max_spread_num = spread_num;
                        block_num = block;
                        isolate.x = i;
                        isolate.y = j;
                    }
                }
            ans += block_num;

            // 扩散
            vector<vector<int>> new_grid = grid;
            visited.assign(n, vector<bool>(m, false));
            for(const Point &p: cc)
            {
                if(p.x == isolate.x && p.y == isolate.y)
                    label_isolate(grid, visited, new_grid, p.x, p.y);
                else
                    spread(grid, visited, new_grid, p.x, p.y);
            }
            // grid.swap(new_grid);
            grid = new_grid;
            if(block_num == 0)
                return ans;
        }
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void spread(vector<vector<int>>& grid, vector<vector<bool>>& visited, vector<vector<int>>& new_grid, int i, int j)
    {
        if(visited[i][j])
            return;
        visited[i][j] = true;
        if(grid[i][j] == 0)
        {
            new_grid[i][j] = 1;
            return;
        }
        if(grid[i][j] == 2)
            return;
        // grid[i][j] = 1

        int n = grid.size();
        int m = grid[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            spread(grid, visited, new_grid, x, y);
        }
    }

    void label_isolate(vector<vector<int>>& grid, vector<vector<bool>>& visited, vector<vector<int>>& new_grid, int i, int j)
    {
        if(grid[i][j] == 2)
            return;
        if(grid[i][j] == 0)
            return;
        // grid[i][j] == 1
        if(visited[i][j])
            return;
        visited[i][j] = true;
        new_grid[i][j] = 2;

        int n = grid.size();
        int m = grid[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            label_isolate(grid, visited, new_grid, x, y);
        }
    }

    void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, vector<vector<bool>>& visited2, int i, int j, int& spread_num, int& block)
    {
        if(grid[i][j] == 0)
        {
            ++block;
            if(!visited2[i][j])
            {
                visited2[i][j] = true;
                ++spread_num;
            }
            return;
        }
        if(grid[i][j] == 2)
            return;
        // grid[i][j] = 1
        if(visited[i][j])
            return;

        visited[i][j] = true;
        int n = grid.size();
        int m = grid[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            dfs(grid, visited, visited2, x, y, spread_num, block);
        }
    }
};
