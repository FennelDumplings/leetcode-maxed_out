// prob1632: Rank Transform of a Matrix

/*
 * https://leetcode-cn.com/problems/rank-transform-of-a-matrix/
 */

#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int N)
    {
        _father.assign(N, -1);
        _rank.assign(N, 0);
        _weight.assign(N, -1);
        for(int i = 0; i < N; ++i)
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
    }

    void update(int x, int val)
    {
        x = _find(x);
        _weight[x] = max(_weight[x], val);
    }

    int query(int x)
    {
        return _weight[_find(x)];
    }

    int get_root(int x)
    {
        return _find(x);
    }

private:
    vector<int> _father;
    vector<int> _rank;
    vector<int> _weight; // idx -> val;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]) ;
    }
};

class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int N = n * m;
        vector<vector<int>> g(N);
        vector<int> indegrees(N, -1);
        map<int, vector<int>> mapping;
        UnionFindSet unionfindset(N);
        // 维护连通分量的并查集
        for(int i = 0; i < n; ++i)
        {
            mapping.clear();
            for(int j = 0; j < m; ++j)
                mapping[matrix[i][j]].push_back(i * m + j);
            auto it = mapping.begin();
            while(it != mapping.end())
            {
                if((it -> second).size() > 1)
                    for(int u: it -> second)
                        unionfindset.merge(u, (it -> second)[0]);
                ++it;
            }
        }
        for(int j = 0; j < m; ++j)
        {
            mapping.clear();
            for(int i = 0; i < n; ++i)
                mapping[matrix[i][j]].push_back(i * m + j);
            auto it = mapping.begin();
            while(it != mapping.end())
            {
                if((it -> second).size() > 1)
                    for(int u: it -> second)
                        unionfindset.merge(u, (it -> second)[0]);
                ++it;
            }
        }

        // 仅用代表元建图
        for(int i = 0; i < n; ++i)
        {
            mapping.clear();
            for(int j = 0; j < m; ++j)
                mapping[matrix[i][j]].push_back(i * m + j);
            auto it = mapping.begin();
            int start = unionfindset.get_root((it -> second)[0]);
            if(indegrees[start] == -1)
                indegrees[start] = 0;
            while(next(it) != mapping.end())
            {
                int u = unionfindset.get_root((it -> second)[0]);
                int v = unionfindset.get_root((next(it) -> second)[0]);
                if(indegrees[v] == -1)
                    indegrees[v] = 0;
                ++indegrees[v];
                g[u].push_back(v);
                ++it;
            }
        }
        for(int j = 0; j < m; ++j)
        {
            mapping.clear();
            for(int i = 0; i < n; ++i)
                mapping[matrix[i][j]].push_back(i * m + j);
            auto it = mapping.begin();
            int start = unionfindset.get_root((it -> second)[0]);
            if(indegrees[start] == -1)
                indegrees[start] = 0;
            while(next(it) != mapping.end())
            {
                int u = unionfindset.get_root((it -> second)[0]);
                int v = unionfindset.get_root((next(it) -> second)[0]);
                if(indegrees[v] == -1)
                    indegrees[v] = 0;
                ++indegrees[v];
                g[u].push_back(v);
                ++it;
            }
        }

        // 拓扑排序
        queue<int> q;
        for(int i = 0; i < N; ++i)
        {
            int u = unionfindset.get_root(i);
            if(u != i)
                continue;
            if(indegrees[u] == 0)
            {
                q.push(u);
                unionfindset.update(u, 1);
            }
        }
        vector<int> level_nodes;
        int level = 1;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(int u: level_nodes)
            {
                for(int v: g[u])
                {
                    --indegrees[v];
                    if(indegrees[v] == 0)
                    {
                        q.push(v);
                        unionfindset.update(v, level + 1);
                    }
                }
            }
            ++level;
        }

        vector<vector<int>> result(n, vector<int>(m, -1));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                result[i][j] = unionfindset.query(i * m + j);
        return result;
    }
};
