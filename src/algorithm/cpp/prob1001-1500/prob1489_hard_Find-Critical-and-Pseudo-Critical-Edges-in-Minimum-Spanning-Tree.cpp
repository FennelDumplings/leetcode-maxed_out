// prbo1489: Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

/*
 * https://leetcode-cn.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int N=0)
    {
        this -> N = N;
        init();
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y)
            return;
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    void init()
    {
        _father.assign(N, 0);
        _rank.assign(N, 0);
        for(int i = 0; i < N; ++i)
            _father[i] = i;
    }

    int get(int x)
    {
        return _find(x);
    }

private:
    int N;
    vector<int> _father;
    vector<int> _rank;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

struct Edge
{
    int u, v, w, id;
    Edge(){}
    Edge(int u, int v, int w, int id):u(u),v(v),w(w),id(id){}
};

struct Cmp
{
    bool operator()(const Edge& e1, const Edge& e2) const
    {
        return e1.w < e2.w;
    }
};

class Solution_2 {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        N = n;
        unionfindset = UnionFindSet(n);
        int m = edges.size();
        for(int i = 0; i < m; ++i)
            es.emplace_back(edges[i][0], edges[i][1], edges[i][2], i);
        sort(es.begin(), es.end(), Cmp());
        vector<vector<int>> result(2);
        int MST = kruskal(0, 0, -1);
        for(int i = 0; i < m; ++i)
        {
            unionfindset.init();
            int mst1 = kruskal(0, 0, i);
            if(mst1 == -1 || mst1 > MST)
            {
                result[0].push_back(i);
                continue;
            }
            unionfindset.init();
            unionfindset.merge(edges[i][0], edges[i][1]);
            int mst2 = kruskal(1, edges[i][2], -1);
            if(mst2 <= MST)
                result[1].push_back(i);
        }
        return result;
    }

private:
    UnionFindSet unionfindset;
    vector<Edge> es;
    int N;

    int kruskal(int chosen, int start_cost, int delete_id)
    {
        int cnt = chosen;
        int cost = start_cost;
        // 边数小于 n - 1，不连通，返回 -1
        for(const Edge &e: es)
        {
            int u = e.u, v = e.v, w = e.w, id = e.id;
            if(id == delete_id)
                continue;
            if(unionfindset.same(u, v))
                continue;
            cost += w;
            unionfindset.merge(u, v);
            ++cnt;
            if(cnt == N - 1)
                break;
        }
        if(cnt < N - 1)
            return -1;
        return cost;
    }
};

#include <map>

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // 初始化
        unionfindset = UnionFindSet(n);
        dfn = vector<int>(n);
        low = vector<int>(n);
        NG = vector<vector<NG_Edge>>(n);
        int m = edges.size();
        bridge = vector<bool>(m, false);

        // mapping[x] := 权值为 x 的边集合
        map<int, vector<Edge>> mapping;
        for(int i = 0; i < m; ++i)
            mapping[edges[i][2]].emplace_back(edges[i][0], edges[i][1], i);

        vector<bool> optional(m, false);
        vector<Edge> level_es;
        for(const auto &item: mapping)
        {
            const vector<Edge> &es = item.second;
            level_es.clear();
            for(const Edge &e: es)
            {
                // u, v 为缩点后的编号
                int u = unionfindset.get(e.u);
                int v = unionfindset.get(e.v);
                if(u == v) continue;
                // 建缩点图：在 NG 中将 u, v 连边
                optional[e.id] = true;
                NG[u].emplace_back(v, e.id);
                NG[v].emplace_back(u, e.id);
                level_es.emplace_back(u, v, e.id);
            }
            // 开始处理缩点图的每条边
            for(Edge &e: level_es)
            {
                // 只需要将连边的点的 dfn 初始化
                // 如果所有点都初始化，时间复杂度会退化
                dfn[e.u] = 0;
                dfn[e.v] = 0;
            }
            // 因为 level_es 中的边可能形成多个连通分量，因此每个点都要尝试找桥
            for(Edge &e: level_es)
            {
                if(dfn[e.u] == 0) // 该连通分量之前没找过
                    find_bridge(e.u);
                if(dfn[e.v] == 0) // 该连通分量之前没找过
                    find_bridge(e.v);
            }
            // 处理完缩点图的每条边之后，将缩点图清空
            // 并将缩点图中的连通分量缩点
            for(Edge &e: level_es)
            {
                NG[e.u].clear();
                NG[e.v].clear();
                unionfindset.merge(e.u, e.v);
            }
        }

        vector<vector<int>> result(2);
        for(int i = 0; i < m; ++i)
        {
            if(!optional[i]) continue;
            if(bridge[i])
                result[0].push_back(i);
            else
                result[1].push_back(i);
        }
        return result;
    }

private:
    UnionFindSet unionfindset;
    vector<int> dfn;
    vector<int> low;
    vector<bool> bridge;
    struct Edge
    {
        int u, v, id;
        Edge(int u, int v, int id):u(u),v(v),id(id){}
    };
    struct NG_Edge
    {
        int v, id;
        NG_Edge(int v, int id):v(v),id(id){}
    };
    vector<vector<NG_Edge>> NG;

    void find_bridge(int S)
    {
        int dfnid = 0;
        dfs(S, -1, dfnid);
    }

    void dfs(int node, int prev, int& dfnid)
    {
        if(dfn[node] != 0)
            return;
        dfn[node] = ++dfnid;
        low[node] = dfnid;
        int min_low = dfnid;
        int cnt = 0;
        for(NG_Edge e: NG[node])
        {
            // (node, son) 这条边
            int son = e.v;
            if(son == prev)
            {
                if(++cnt > 1)
                    min_low = min(min_low, dfn[son]);
                continue;
            }
            dfs(son, node, dfnid);
            if(low[son] > dfn[node]) // 找到桥边
                bridge[e.id] = true;
            min_low = min(min_low, low[son]);
        }
        low[node] = min_low;
    }
};
