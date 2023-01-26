// prob200: Number of Islands

/*
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 */

/*
 * Example 1:
 * Input:
 * 11110
 * 11010
 * 11000
 * 00000
 * Output: 1
 * Example 2:
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 * Output: 3
 */

#include <vector>
#include <queue>

using namespace std;

// BFS
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        queue<pair<int, int> > q;
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        int result = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == '1' && !visited[i][j])
                {
                    q.push(pair<int, int>(i, j));
                    visited[i][j] = true;
                    while(!q.empty())
                    {
                        pair<int, int> cur = q.front();
                        q.pop();
                        if(_check(cur.first + 1, cur.second, grid, visited))
                        {

                            q.push(pair<int, int>(cur.first + 1, cur.second));
                            visited[cur.first + 1][cur.second] = true;
                        }
                        if(_check(cur.first - 1, cur.second, grid, visited))
                        {
                            q.push(pair<int, int>(cur.first - 1, cur.second));
                            visited[cur.first - 1][cur.second] = true;
                        }
                        if(_check(cur.first, cur.second + 1, grid, visited))
                        {
                            q.push(pair<int, int>(cur.first, cur.second + 1));
                            visited[cur.first][cur.second + 1] = true;
                        }
                        if(_check(cur.first, cur.second - 1, grid, visited))
                        {
                            q.push(pair<int, int>(cur.first, cur.second - 1));
                            visited[cur.first][cur.second - 1] = true;
                        }
                    }
                    ++result;
                }
            }
        return result;
    }

private:
    bool _check(int i, int j, vector<vector<char>>& grid, vector<vector<bool> >& visited)
    {
        int n = grid.size(), m = grid[0].size();
        if(i < 0 || i >= n || j < 0 || j >= m)
            return false;
        if(visited[i][j])
            return false;
        if(grid[i][j] == '0')
            return false;
        return true;
    }
};

// 并查集
class UnionFindSet {
public:
    UnionFindSet(const vector<vector<char> >& grid)
    {
        int n = grid.size(), m = grid[0].size();
        _set_size = 0;
        _item_size = 0;
        _father = vector<int>(n * m, -1);
        _rank = vector<int>(n * m, 0);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == '1')
                {
                    ++_set_size;
                    ++_item_size;
                    _father[_get_index(i, j, m)] = _get_index(i, j, m);
                }
            }
    }

    ~UnionFindSet(){}

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y) return;

        // 此时 x, y 是所在树的根
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }

        --_set_size;
    }

    int item_size()
    {
        return _item_size;
    }

    int set_size()
    {
        return _set_size;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    int _item_size;
    int _set_size;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        else
            return _father[x] = _find(_father[x]); // 路径压缩
    }

    int _get_index(int i, int j, int m)
    {
        return i * m + j;
    }
};

class Solution_2 {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        UnionFindSet unionfindset(grid);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == '1')
                {
                    if(_check(i + 1, j, grid))
                        unionfindset.merge(_get_index(i, j, m), _get_index(i + 1, j, m));
                    if(_check(i, j + 1, grid))
                        unionfindset.merge(_get_index(i, j, m), _get_index(i, j + 1, m));
                }
            }
        return unionfindset.set_size();
    }

private:
    bool _check(int i, int j, vector<vector<char>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        if(i >= n ||j >= m)
            return false;
        if(grid[i][j] == '0')
            return false;
        return true;
    }

    int _get_index(int i, int j, int m)
    {
        return i * m + j;
    }
};
