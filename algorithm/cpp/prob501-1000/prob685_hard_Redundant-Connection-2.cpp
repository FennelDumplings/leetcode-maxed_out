// prob685: Redundant Connection II

/*
 * In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for
 * which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
 * The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N),
 * with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
 * The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that
 * represents a directed edge connecting nodes u and v, where u is a parent of child v.
 * Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers,
 * return the answer that occurs last in the given 2D-array.
 */

/*
 * Example 1:
 * Input: [[1,2], [1,3], [2,3]]
 * Output: [2,3]
 * Explanation: The given directed graph will be like this:
 *   1
 *  / \
 * v   v
 * 2-->3
 * Example 2:
 * Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
 * Output: [4,1]
 * Explanation: The given directed graph will be like this:
 * 5 <- 1 -> 2
 *      ^    |
 *      |    v
 *      4 <- 3
 */

/*
 * Note:
 * The size of the input 2D-array will be between 3 and 1000.
 * Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
 */

#include <vector>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        _father = vector<int>(n + 1, -1);
        _rank = vector<int>(n + 1, 1);
        for(int i = 1; i <= n; ++i)
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

        if(x == y) return;
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
            _father[y] = x;
        if(_rank[x] == _rank[y])
            ++_rank[x];
    }

private:
    vector<int> _father;
    vector<int> _rank;

    int _find(int x)
    {
        if(_father[x] == x) return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<int> rev(N + 1, -1);
        vector<int> tmp1(2, -1);
        vector<int> tmp2(2, -1);
        for(const vector<int> &edge: edges)
        {
            if(rev[edge[1]] != -1) // 找到入度为 2 的
            {
                tmp1 = edge;
                tmp2[0] = rev[edge[1]];
                tmp2[1] = edge[1];
                break;
            }
            rev[edge[1]] = edge[0];
        }
        if(tmp1[0] == -1)
        {
            UnionFindSet unionfindset(N);
            for(const vector<int> &edge: edges)
            {
                int x = edge[0], y = edge[1];
                if(unionfindset.same(x, y))
                    return edge;
                unionfindset.merge(x, y);
            }
            return vector<int>(2, -1);
        }
        UnionFindSet unionfindset(N);
        for(const vector<int> &edge: edges)
        {
            if(edge == tmp1)
                continue;
            int x = edge[0], y = edge[1];
            if(unionfindset.same(x, y))
                return tmp2;
            unionfindset.merge(x, y);
        }
        return tmp1;
    }
};
