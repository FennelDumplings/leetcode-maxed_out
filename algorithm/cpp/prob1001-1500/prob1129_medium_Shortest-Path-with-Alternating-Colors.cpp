// prob1129: Shortest Path with Alternating Colors

/*
 * https://leetcode-cn.com/problems/shortest-path-with-alternating-colors/
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct EdgeTo
{
    int v;
    int color;
    EdgeTo(int v, int c):v(v),color(c){}
};

struct State
{
    int u;
    int d;
    int c;
    State(int u, int d, int c):u(u),d(d),c(c){}
};

struct HeapCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.d > s2.d;
    }
};

class Solution {
public:
    vector<int> dijkstra(vector<vector<EdgeTo>>& g, State s)
    {
        int n = g.size();
        priority_queue<State, vector<State>, HeapCmp> pq;
        pq.push(s);
        vector<vector<int>> d(2, vector<int>(n, INT_MAX / 2)); // d[c][i] := 经过c色边进入 i的 0 -> i 最短路径
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(d[cur.c][cur.u] != INT_MAX / 2)
                continue;
            d[cur.c][cur.u] = cur.d;
            for(EdgeTo &son: g[cur.u])
            {
                if(d[son.color][son.v] != INT_MAX / 2)
                    continue;
                if(son.color == cur.c)
                    continue;
                pq.push(State(son.v, cur.d + 1, son.color));
            }
        }
        vector<int> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = min(d[0][i], d[1][i]);
        return ans;
    }

    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<EdgeTo>> g(n);
        for(vector<int> &e: red_edges)
            g[e[0]].emplace_back(e[1], 0);
        for(vector<int> &e: blue_edges)
            g[e[0]].emplace_back(e[1], 1);

        vector<int> d1 = dijkstra(g, State(0, 0, 0));
        vector<int> d2 = dijkstra(g, State(0, 0, 1));

        vector<int> ans(n);
        for(int i = 0; i < n; ++i)
        {
            ans[i] = min(d1[i], d2[i]);
            if(ans[i] == INT_MAX / 2)
                ans[i] = -1;
        }
        return ans;
    }
};
