// prob323: umber of Connected Components in an Undirected Graph

/*
 * Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes),
 * write a function to find the number of connected components in an undirected graph.
 */

/*
 * Note
 * You can assume that no duplicate edges will appear in edges.
 * Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
 */

#include <vector>

using namespace std;

class UnionFindSet {
public:
    UnionFindSet(int m)
    {
        _item_size = m;
        _set_size = m;
        _father = vector<int>(_item_size, 0);
        _rank = vector<int>(_item_size, 0);
        for(int i = 0; i < _item_size; ++i)
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

    int item_size()
    {
        return _item_size;
    }

private:
    int _item_size;
    int _set_size;
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
    int countComponents(int n, vector<vector<int>>& edges) {
        if(edges.empty()) return n;
        UnionFindSet unionfindset(n);
        for(vector<int> edge: edges)
            unionfindset.merge(edge[0], edge[1]);
        return unionfindset.set_size();
    }
};
