// 1319: Minimum Flips to Make a OR b Equal to c

/*
 * https://leetcode-cn.com/problems/number-of-operations-to-make-network-connected/
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
        cc_num = n;
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
        }
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
        --cc_num;
    }

    int get_cc_num()
    {
        return cc_num;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    int cc_num;

    int _find(int x)
    {
        if(x == _father[x])
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int m = connections.size();
        if(m < n - 1)
            return -1;
        UnionFindSet unionfindset(n);
        for(vector<int> &e: connections)
            unionfindset.merge(e[0], e[1]);
        return unionfindset.get_cc_num() - 1;
    }
};
