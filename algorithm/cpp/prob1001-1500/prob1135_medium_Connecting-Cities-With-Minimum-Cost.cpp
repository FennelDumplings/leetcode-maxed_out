// prob1135: Connecting Cities With Minimum Cost

/*
 * There are N cities numbered from 1 to N.
 * You are given connections, where each connections[i] = [city1, city2, cost] represents the cost to
 * connect city1 and city2 together.  (A connection is bidirectional: connecting city1 and city2 is the same as connecting city2 and city1.)
 * Return the minimum cost so that for every pair of cities, there exists a path of connections (possibly of length 1) that
 * connects those two cities together.  The cost is the sum of the connection costs used. If the task is impossible, return -1.
 */

/*
 * Note:
 * 1 <= N <= 10000
 * 1 <= connections.length <= 10000
 * 1 <= connections[i][0], connections[i][1] <= N
 * 0 <= connections[i][2] <= 10^5
 * connections[i][0] != connections[i][1]
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// prim
class Solution_1 {
public:
    int minimumCost(int N, vector<vector<int>>& connections) {
        vector<vector<vector<int> > > g(N + 1);
        for(const vector<int> &connection: connections)
        {
            int x = connection[0], y = connection[1], w = connection[2];
            g[x].push_back(vector<int>({w, y}));
            g[y].push_back(vector<int>({w, x}));
        }
        priority_queue<vector<int> > pq;
        pq.push({0, 1});
        vector<int> visited(N + 1, false);
        visited[0] = true;
        int cost = 0;
        while(!pq.empty())
        {
            vector<int> cur = pq.top();
            pq.pop();
            if(visited[cur[1]])
                continue;
            visited[cur[1]] = true;
            cost += -cur[0];
            for(vector<int> son: g[cur[1]])
            {
                if(visited[son[1]])
                    continue;
                pq.push({-son[0], son[1]});
            }
        }
        for(bool v: visited)
            if(!v)
                return -1;
        return cost;
    }
};

// Kruskal
class UnionFindSet
{
public:
    UnionFindSet(int N)
    {
        _father = vector<int>(N + 1, -1);
        _rank = vector<int>(N + 1, 1);
        for(int i = 1; i <= N; ++i)
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
    int minimumCost(int N, vector<vector<int>>& connections) {
        sort(connections.begin(), connections.end(), Cmp());
        UnionFindSet unionfindset(N);
        int cost = 0;
        int cnt = 0;
        for(const vector<int>& connection: connections)
        {
            int x = connection[0], y = connection[1], w = connection[2];
            if(unionfindset.same(x, y))
                continue;
            cost += w;
            unionfindset.merge(x, y);
            ++cnt;
            if(cnt == N - 1)
                break;
        }
        if(cnt < N - 1)
            return -1;
        return cost;
    }

private:
    struct Cmp
    {
        bool operator() (const vector<int>& edge1, const vector<int>& edge2)
        {
            if(edge1[2] == edge2[2])
                return edge1 < edge2;
            return edge1[2] < edge2[2];
        }
    };
};
