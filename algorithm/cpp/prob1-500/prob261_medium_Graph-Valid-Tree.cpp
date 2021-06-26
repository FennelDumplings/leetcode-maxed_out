// prob261: Graph Valid Tree

/*
 * Given n nodes labeled from 0 to n-1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.
 */

/*
 * Example 1:
 * Input: n = 5, and edges = [[0,1], [0,2], [0,3], [1,4]]
 * Output: true
 * Example 2:
 * Input: n = 5, and edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
 * Output: false
 */

#include <vector>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        _rank = vector<int>(n, 0);
        _father = vector<int>(n, -1);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
    }

    bool same(int a, int b)
    {
        return _find(a) == _find(b);
    }

    void merge(int a, int b)
    {
        int x = _find(a);
        int y = _find(b);

        if(x == y) return;
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

private:
    vector<int> _rank;
    vector<int> _father;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if(n == 0) return true;
        int n_edge = edges.size();
        if(n_edge != n - 1)
            return false;
        UnionFindSet unionfindset(n);
        for(const vector<int>& edge: edges)
        {
            if(unionfindset.same(edge[0], edge[1]))
                return false;
            unionfindset.merge(edge[0], edge[1]);
        }
        return true;
    }
};
