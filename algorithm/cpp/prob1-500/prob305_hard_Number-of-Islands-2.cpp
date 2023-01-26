// prob305: Number of Islands II

/*
 * A 2d grid map of m rows and n columns is initially filled with water.
 * We may perform an addLand operation which turns the water at position (row, col) into a land.
 * Given a list of positions to operate, count the number of islands after each addLand operation.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 */

/*
 * Follow up:
 * Can you do it in time complexity O(k log mn), where k is the length of the positions?
 */

#include <vector>

using namespace std;

class UnionFindSet {
public:
    UnionFindSet(int n)
    {
        _item_size = 0;
        _set_size = 0;
        _father = vector<int>(n, -1);
        _rank = vector<int>(n, 0);
    }

    ~UnionFindSet(){}

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    bool check(int x)
    {
        // 查看 x 是否被置 1 了
        return _father[x] != -1;
    }

    void modify(int x)
    {
        if(!check(x))
        {
            _father[x] = x ;
            ++_item_size;
            ++_set_size;
        }
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

    int set_num()
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
            // return _find(_father[x]);
    }
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        UnionFindSet unionfindset(m * n);
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        vector<int> result;
        for(vector<int> pos: positions)
        {
            int cur_index = _get_index(pos[0], pos[1], n);
            unionfindset.modify(cur_index);
            for(int d = 0; d < 4; ++d)
            {
                if(_valid(pos[0] + dx[d], pos[1] + dy[d], m, n))
                {
                    int next_index = _get_index(pos[0] + dx[d], pos[1] + dy[d], n);
                    if(unionfindset.check(next_index))
                        unionfindset.merge(cur_index, next_index);
                }
            }
            result.push_back(unionfindset.set_num());
        }
        return result;
    }

private:
    bool _valid(int i, int j, int n, int m)
    {
        return (i >= 0 && i < n && j >= 0 && j < m);
    }

    int _get_index(int i, int j, int m)
    {
        return i * m + j;
    }
};
