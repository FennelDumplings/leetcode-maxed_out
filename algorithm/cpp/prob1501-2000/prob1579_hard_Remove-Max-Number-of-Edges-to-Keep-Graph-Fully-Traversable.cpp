// prob1579: Remove Max Number of Edges to Keep Graph Fully Traversable

/*
 * https://leetcode-cn.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
 */

#include <vector>

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
        return _set_size - 1;
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

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UnionFindSet unionfindset1(n + 1);
        for(const vector<int> &edge: edges)
        {
            if(edge[0] == 3 || edge[0] == 1)
            {
                unionfindset1.merge(edge[1], edge[2]);
            }
        }
        if(unionfindset1.set_size() > 1)
            return -1;
        UnionFindSet unionfindset2(n + 1);
        for(const vector<int> &edge: edges)
        {
            if(edge[0] == 3 || edge[0] == 2)
            {
                unionfindset2.merge(edge[1], edge[2]);
            }
        }
        if(unionfindset2.set_size() > 1)
            return -1;
        UnionFindSet unionfindset(n + 1);
        int k = 0;
        for(const vector<int> &edge: edges)
        {
            if(edge[0] == 3)
            {
                unionfindset.merge(edge[1], edge[2]);
                ++k;
            }
        }
        int set_size = unionfindset.set_size();
        int ans = 0;
        for(const vector<int> &edge: edges)
        {
            if(edge[0] == 1 || edge[0] == 2)
                ++ans;
        }
        ans -= (set_size - 1) * 2;
        ans += k - (n - set_size);
        return ans;
    }
};
