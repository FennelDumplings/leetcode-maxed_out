// prob684: Redundant Connection

/*
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 * The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N),
 * with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
 * The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that
 * represents an undirected edge connecting nodes u and v.
 * Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers,
 * return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.
 */

/*
 * Note:
 * The size of the input 2D-array will be between 3 and 1000.
 * Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
 */

/*
 * Example 1:
 * Input: [[1,2], [1,3], [2,3]]
 * Output: [2,3]
 * Explanation: The given undirected graph will be like this:
 *   1
 *  / \
 * 2 - 3
 * Example 2:
 * Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
 * Output: [1,4]
 * Explanation: The given undirected graph will be like this:
 * 5 - 1 - 2
 *     |   |
 *     4 - 3
 */

#include <vector>

using namespace std;

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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        UnionFindSet unionfindset(N);
        for(vector<int> &edge: edges)
        {
            int x = edge[0], y = edge[1];
            if(unionfindset.same(x, y))
                return vector<int>({x, y});
            else
                unionfindset.merge(x, y);
        }
        return vector<int>();
    }
};


//  DFS
/*
bool dfs(const vector<vector<int>>& g, int u, vector<bool>& visited, int s)
{
    visited[u] = true;
    for(int v: g[u])
    {
        if(visited[v])
            continue;
        if(v == s)
            return true;
        if(dfs(g, v, visited, s))
        {
            visited[u] = false;
            return true;
        }
    }
    visited[u] = false;
    return false;
}

bool is_cycle(const vector<vector<int>>& g, int u, int v, vector<bool>& visited)
{
    // (u, v)
    // 是否存在另一条 u -> v
    visited[u] = true;
    for(int son: g[u])
    {
        if(son == v) continue;
        if(dfs(g, son, visited, v))
        {
            visited[u] = false;
            return true;
        }
    }
    visited[u] = false;
    return false;
}

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<vector<int>> g(N + 1);
        for(const vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(N, false);
        for(int i = N - 1; i >= 0; --i)
        {
            if(is_cycle(g, edges[i][0], edges[i][1], visited))
                return edges[i];
        }
        return {};
    }
};
*/


//BFS
#include <queue>
bool bfs(const vector<vector<int>>& g, vector<bool>& visited, int start, int s)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int son: g[u])
        {
            if(visited[son])
                continue;
            if(son == s)
                return true;
            visited[son] = true;
            q.push(son);
        }
    }
    return false;
}

bool is_cycle(const vector<vector<int>>& g, int u, int v, vector<bool>& visited)
{
    for(int son: g[u])
    {
        if(son == v)
            continue;
        if(bfs(g, visited, son, v))
            return true;
    }
    return false;
}

class Solution_3 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<vector<int>> g(N + 1);
        for(const vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(N, false);
        for(int i = N - 1; i >= 0; --i)
        {
            visited.assign(N, false);
            if(is_cycle(g, edges[i][0], edges[i][1], visited))
                return edges[i];
        }
        return {};
    }
};

// Topsort
void topsort(const vector<vector<int>>& g, vector<int>& degrees)
{
    int n = g.size(); // g 从 1 开始，共 n - 1 个点
    for(int u = 0; u < n; ++u)
        degrees[u] = g[u].size();

    queue<int> q;
    vector<bool> visited(n, false);
    for(int u = 0; u < n; ++u)
        if(degrees[u] == 1)
        {
            q.push(u);
            visited[u] = true;
        }

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v: g[u])
        {
            if(visited[v])
                continue;
            --degrees[v];
            if(degrees[v] == 1)
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<vector<int>> g(N + 1);
        for(const vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        vector<int> degrees(N + 1, 0);
        topsort(g, degrees);
        for(int i = N - 1; i >= 0; --i)
            if(degrees[edges[i][0]] > 1 && degrees[edges[i][1]] > 1)
                return edges[i];
        return {};
    }
};
