// prob803: Bricks Falling When Hit

/*
 * https://leetcode-cn.com/problems/bricks-falling-when-hit/
 */

#include <vector>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        _father.assign(n, -1);
        _rank.assign(n, 0);
        _weight.assign(n, 1);
        _label.assign(n, false);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
    }

    void set_label(int x)
    {
        _label[_find(x)] = true;
    }

    bool check_label(int x)
    {
        return _label[_find(x)];
    }

    int merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y)
            return 0;

        int ans = 0;
        if(!_label[x] && _label[y])
            ans = _weight[x];
        else if(_label[x] && !_label[y])
            ans = _weight[y];

        if(_rank[x] < _rank[y])
        {
            _father[x] = y;
            _label[y] = _label[y] || _label[x];
            _weight[y] += _weight[x];
        }
        else
        {
            _father[y] = x;
            _label[x] = _label[y] || _label[x];
            _weight[x] += _weight[y];
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
        return ans;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    vector<int> _weight;
    vector<bool> _label;

    int _find(int x)
    {
        if(x == _father[x])
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    vector<int> hitBricks(const vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> new_grid = grid;
        for(vector<int> &coord: hits)
            new_grid[coord[0]][coord[1]] = 0;
        UnionFindSet unionfindset(n * m);
        for(int j = 0; j < m; ++j)
            unionfindset.set_label(j);
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(new_grid[i][j] == 0)
                    continue;
                if(visited[i][j])
                    continue;
                visited[i][j] = true;
                dfs(new_grid, unionfindset, i, j, visited);
            }
        int M = hits.size();
        vector<int> result(M);
        for(int k = M - 1; k >= 0; --k)
        {
            int i = hits[k][0], j = hits[k][1];
            if(grid[i][j] == 0)
                continue;
            int u = i * m + j;
            int cnt = 0;
            bool label = unionfindset.check_label(u);
            for(int d = 0; d < 4; ++d)
            {
                int x = i + dx[d], y = j + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(new_grid[x][y] == 1)
                {
                    int v = x * m + y;
                    int c = unionfindset.merge(u, v);
                    cnt += c;
                }
            }
            if(cnt > 0)
            {
                result[k] = cnt - 1;
                if(label)
                    ++result[k];
            }
            new_grid[i][j] = 1;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void dfs(const vector<vector<int>>& new_grid, UnionFindSet& unionfindset, int i, int j, vector<vector<bool>>& visited)
    {
        int n = new_grid.size(), m = new_grid[0].size();
        int u = i * m + j;
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(new_grid[x][y] == 0)
                continue;
            if(visited[x][y])
                continue;
            visited[x][y] = true;
            int v = x * m + y;
            unionfindset.merge(u, v);
            dfs(new_grid, unionfindset, x, y, visited);
        }
    }
};
