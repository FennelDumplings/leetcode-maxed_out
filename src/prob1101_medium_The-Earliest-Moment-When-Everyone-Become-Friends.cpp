// prob1101: The Earliest Moment When Everyone Become Friends

/*
 * https://leetcode-cn.com/problems/the-earliest-moment-when-everyone-become-friends/
 */

#include <vector>
#include <algorithm>

using namespace std;

class UnionFindSet {
public:
    UnionFindSet(int n)
    {
        _set_size = n;
        _father = vector<int>(n, -1);
        _rank = vector<int>(n, 0);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
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

    int set_size()
    {
        return _set_size;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    int _set_size;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        else
            return _father[x] = _find(_father[x]); // 路径压缩
    }
};

struct Cmp
{
    bool operator()(const vector<int>& r1, const vector<int>& r2) const
    {
        return r1[0] < r2[0];
    }
};

class Solution {
public:
    int earliestAcq(vector<vector<int>>& logs, int N) {
        vector<vector<int>> g(N);
        UnionFindSet unionfindset(N);
        if(unionfindset.set_size() == 1)
            return 0;
        sort(logs.begin(), logs.end(), Cmp());
        for(const vector<int>& record: logs)
        {
            int t = record[0];
            int u = record[1];
            int v = record[2];
            unionfindset.merge(u, v);
            if(unionfindset.set_size() == 1)
                return t;
        }
        return -1;
    }
};
