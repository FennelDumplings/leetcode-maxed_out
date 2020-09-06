// prob1568: Minimum Number of Days to Disconnect Island

/*
 * https://leetcode-cn.com/problems/minimum-number-of-days-to-disconnect-island/
 */

#include <vector>

using namespace std;

class Solution_2 {
public:
    int minDays(vector<vector<int>>& grid)
    {

        int n = grid.size(), m = grid[0].size();
        int cnt = connect_cnt(grid);
        if(cnt > 1 || cnt == 0)
            return 0;
        // cnt = 1
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


// 割点: 显式建立邻接表
class Solution {
public:
    int minDays(vector<vector<int>>& grid)
    {

        int n = grid.size(), m = grid[0].size();
        int cnt = connect_cnt(grid);
        if(cnt > 1 || cnt == 0)
            return 0;
        // cnt = 1
        // 显式建邻接表
        int size = 0;
        vector<vector<int>> g(n * m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 0)
                    continue;
                ++size;
                // grid[i][j] = 1
                int u = ij2id(i, j, m);
                for(int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if(x < 0 || x >= n || y < 0 || y >= m)
                        continue;
                    if(grid[x][y] == 0)
                        continue;
                    int v = ij2id(x, y, m);
                    g[u].push_back(v);
                }
            }
        if(size <= 2)
            return size;
        vector<int> cut_points = find_cut_point(g);
        if(!cut_points.empty())
            return 1;
        return 2;
    }

private:
    int ij2id(int i, int j, int m)
    {
        return i * m + j;
    }

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

    vector<int> find_cut_point(const vector<vector<int>>& g)
    {
        int n = g.size();
        vector<bool> visited(n, false);
        vector<int> ord(n, n);
        vector<int> low(n, n);
        vector<int> result;
        int root = -1;
        for(int i = 0; i < n; ++i)
            if(!g[i].empty())
            {
                root = i;
                break;
            }
        if(root == -1) return {};
        dfs(g, root, visited, ord, low, 0, result, root);
        return result;
    }

    bool dfs(const vector<vector<int>>& g, int node, vector<bool>& visited, vector<int>& ord,
            vector<int>& low, int total, vector<int>& result, const int root)
    {
        if(visited[node])
            return false;
        visited[node] = true;
        ord[node] = total;
        low[node] = total;
        int min_low = total;
        int son_cnt = 0; // 记录 DFS 树的子节点树，不含回边
        for(int son: g[node])
        {
            // (node, son) 这条边
            if(!visited[son])
                ++son_cnt;
            bool son_on_dfs_tree = dfs(g, son, visited, ord, low, total + 1, result, root);
            if(son_on_dfs_tree && low[son] >= ord[node] && node != root) // 与寻找桥的算法相比改动的地方
                result.push_back(node);
            min_low = min(min_low, low[son]);
        }
        low[node] = min_low;
        if(node == root && son_cnt > 1)
            result.push_back(node);
        return true;
    }
};


