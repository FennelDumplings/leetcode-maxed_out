// prob1627: Graph Connectivity With Threshold

/*
 * https://leetcode-cn.com/problems/graph-connectivity-with-threshold/
 */

#include <vector>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        // n : 点的个数
        _father = vector<int>(n + 1);
        _rank = vector<int>(n + 1);
        for(int i = 0; i <= n; ++i)
            _father[i] = i;
    }

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
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
        }
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

private:
    vector<int> _father;
    vector<int> _rank;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        UnionFindSet unionfindset(n);
        for(int i = threshold + 1; i <= n; ++i)
            for(int j = i * 2; j <= n; j += i)
                unionfindset.merge(i, j);
        int m = queries.size();
        vector<bool> result(m);
        for(int i = 0; i < m; ++i)
            result[i] = unionfindset.same(queries[i][0], queries[i][1]);
        return result;
    }
};
