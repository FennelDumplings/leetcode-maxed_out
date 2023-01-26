// prob947: Most Stones Removed with Same Row or Column

/*
 * https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column/
 */

#include <vector>
#include <unordered_set>

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

    int find(int x)
    {
        return _find(x);
    }

private:
    vector<int> _father;
    vector<int> _rank;
    int cc_num; // 连通分量个数

    int _find(int x)
    {
        if(x == _father[x])
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        // 0~9999 是行的范围 10000~19999 是列的范围
        UnionFindSet unionfindset(20000);
        unordered_set<int> setting; // 代表元
        for(int i = 0; i < n; ++i)
            unionfindset.merge(stones[i][0], 10000 + stones[i][1]);
        for(int i = 0; i < n; ++i)
            setting.insert(unionfindset.find(stones[i][0]));
        return n - setting.size();
    }
};


