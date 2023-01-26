// prob1168: Optimize Water Distribution in a Village

/*
 * There are n houses in a village. We want to supply water for all the houses by building wells and laying pipes.
 * For each house i, we can either build a well inside it directly with cost wells[i], or pipe in water from another well to it. The costs to lay pipes between houses are given by the array pipes, where each pipes[i] = [house1, house2, cost] represents the cost to connect house1 and house2 together using a pipe. Connections are bidirectional.
 * Find the minimum total cost to supply water to all houses.
 */

/*
 * Example 1:
 * Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
 * Output: 3
 * Explanation:
 * The image shows the costs of connecting houses using pipes.
 * The best strategy is to build a well in the first house with cost 1 and connect the other houses to it with cost 2 so the total cost is 3.
 */

/*
 * Constraints:
 * 1 <= n <= 10000
 * wells.length == n
 * 0 <= wells[i] <= 10^5
 * 1 <= pipes.length <= 10000
 * 1 <= pipes[i][0], pipes[i][1] <= n
 * 0 <= pipes[i][2] <= 10^5
 * pipes[i][0] != pipes[i][1]
 */

#include <vector>
#include <algorithm>

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
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        for(int i = 0; i < n; ++i)
            pipes.push_back(vector<int>{i + 1, n + 1, wells[i]});
        return mst(pipes, n + 1);
    }

private:
    int mst(vector<vector<int>>& edges, int n)
    {
        // Kruskal 接受带权边表
        sort(edges.begin(), edges.end(), Cmp());
        UnionFindSet unionfindset(n + 1);
        int cost = 0;
        int cnt = 0;
        for(const vector<int>& edge: edges)
        {
            int u = edge[0], v = edge[1], w = edge[2];
            if(unionfindset.same(u, v)) continue;
            unionfindset.merge(u, v);
            cost += w;
            ++cnt;
            if(cnt == n - 1)
                break;
        }
        if(cnt < n - 1)
            return -1;
        return cost;
    }

    struct Cmp
    {
        bool operator()(const vector<int>& edge1, const vector<int>& edge2) const
        {
            if(edge1[2] == edge2[2])
                return edge1 < edge2;
            return edge1[2] < edge2[2];
        }
    };
};
