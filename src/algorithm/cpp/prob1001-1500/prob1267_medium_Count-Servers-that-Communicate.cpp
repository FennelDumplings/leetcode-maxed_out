// prob1267: Count Servers that Communicate

/*
 * https://leetcode-cn.com/problems/count-servers-that-communicate/
 */

#include <vector>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        _father.assign(n, 0);
        _rank.assign(n, 0);
        _weight.assign(n, 1);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y)
            return;

        if(_rank[x] < _rank[y])
        {
            _father[x] = y;
            _weight[y] += _weight[x];
        }
        else
        {
            _father[y] = x;
            _weight[x] += _weight[y];
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

    int get(int x)
    {
        return _weight[_find(x)];
    }

private:
    vector<int> _father;
    vector<int> _rank;
    vector<int> _weight;

    int _find(int x)
    {
        if(x == _father[x])
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution_2 {
public:
    int countServers(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        UnionFindSet unionfindset(n * m);
        vector<int> tmp;
        for(int i = 0; i < n; ++i)
        {
            tmp.clear();
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                    tmp.push_back(i * m + j);
            }
            int M = tmp.size();
            for(int k = 1; k < M; ++k)
                unionfindset.merge(tmp[k - 1], tmp[k]);
        }
        for(int j = 0; j < m; ++j)
        {
            tmp.clear();
            for(int i = 0; i < n; ++i)
            {
                if(grid[i][j] == 1)
                    tmp.push_back(i * m + j);
            }
            int M = tmp.size();
            for(int k = 1; k < M; ++k)
                unionfindset.merge(tmp[k - 1], tmp[k]);
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1 && unionfindset.get(i * m + j) == 1)
                    ++ans;
            }
        return ans;
    }
};

// ----


class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        UnionFindSet unionfindset(n * m);
        vector<int> tmp;
        for(int i = 0; i < n; ++i)
        {
            tmp.clear();
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                    tmp.push_back(i * m + j);
            }
            int M = tmp.size();
            for(int k = 1; k < M; ++k)
                unionfindset.merge(tmp[k - 1], tmp[k]);
        }
        for(int j = 0; j < m; ++j)
        {
            tmp.clear();
            for(int i = 0; i < n; ++i)
            {
                if(grid[i][j] == 1)
                    tmp.push_back(i * m + j);
            }
            int M = tmp.size();
            for(int k = 1; k < M; ++k)
                unionfindset.merge(tmp[k - 1], tmp[k]);
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1 && unionfindset.get(i * m + j) == 1)
                    ++ans;
            }
        return ans;
    }
};


