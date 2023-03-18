// prob1617: Count Subtrees With Max Distance Between Cities

/*
 * https://leetcode-cn.com/problems/count-subtrees-with-max-distance-between-cities/
 */

#include <vector>

using namespace std;

class TreeDiameter {
public:
    int solve(const vector<vector<int>>& g, int s) {
        int ans = 0;
        dfs(s, -1, g, ans);
        return ans;
    }

private:
    int dfs(int x, int fa, const vector<vector<int> >& g, int& ans)
    {
        int max1 = 0, max2 = 0;
        for(int v: g[x])
        {
            if(v != fa)
            {
                int t = dfs(v, x, g, ans) + 1;
                if(max1 < t)
                {
                    max2 = max1;
                    max1 = t;
                }
                else if(max2 < t)
                    max2 = t;
            }
        }
        ans = max(ans, (max1 + max2));
        return max1;
    }
};

class Solution_2 {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        vector<vector<int>> chosen_edge;
        TreeDiameter diameter_solver;
        vector<int> result(n - 1);
        for(int state = 1; state < (1 << n); ++state)
        {
            chosen_edge.clear();
            int check_state = 0;
            for(const vector<int> &e: edges)
            {
                if(((state >> (e[0] - 1)) & 1) && ((state >> (e[1] - 1)) & 1))
                {
                    check_state |= (1 << (e[0] - 1));
                    check_state |= (1 << (e[1] - 1));
                    chosen_edge.push_back(e);
                }
            }
            // state 标记的点都有边选上了
            if(check_state != state) continue;
            vector<vector<int> > g(n + 1);
            for(const auto &e: chosen_edge)
            {
                g[e[0]].push_back(e[1]);
                g[e[1]].push_back(e[0]);
            }
            int s = chosen_edge[0][0];
            if(!connect(g, state, s)) continue;
            int d = diameter_solver.solve(g, s);
            ++result[d - 1];
        }
        return result;
    }

private:
    bool connect(const vector<vector<int>>& g, int state, int s)
    {
        dfs(g, s, -1, state);
        return state == 0;
    }

    void dfs(const vector<vector<int>>& g, int u, int prev, int& state)
    {
        state &= ~(1 << (u - 1));
        for(int v: g[u])
            if(v != prev)
                dfs(g, v, u, state);
    }
};


class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        vector<vector<int> > g(n + 1);
        for(const auto &e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<vector<int>> dist(n + 1, vector<int>(n + 1, INT_MAX / 2));
        for(int s = 1; s <= n; ++s)
            bfs(g, s, dist);
        vector<int> result(n - 1);
        for(int i = 1; i < n; ++i)
            for(int j = i + 1; j <= n; ++j)
            {
                int d = dist[i][j];
                cout << i << ' ' << j << " " << d << endl;
                if(d == INT_MAX / 2)
                    continue;
                result[d - 1] += dfs(g, dist, i, j, i, -1);
            }
        return result;
    }

private:
    struct State {
        int v;
        int d;
        State(){}
        State(int v, int d):v(v),d(d){}
    };

    vector<int> visited;
    queue<State> q;

    int dfs(const vector<vector<int>>& g, const vector<vector<int>>& dist, const int i, const int j, int x, int fa)
    {
        int d = dist[i][j];
        int c = 1; // 选 x
        for(int y: g[x])
        {
            // continue 的情况是 y 不可选的情况
            if(y == fa)
                continue;
            if(dist[i][y] > d || dist[j][y] > d)
                continue;
            if(dist[i][y] == d && y < j)
                continue;
            if(dist[j][y] == d && y < i)
                continue;
            c *= dfs(g, dist, i, j, y, x);
        }
        if(dist[i][x] + dist[j][x] > d)
            c++;
        return c;
    }

    void bfs(const vector<vector<int>>& g, int s, vector<vector<int>>& dist)
    {
        int n = g.size() - 1;
        visited.assign(n + 1, 0);
        q.push(State(s, 0));
        visited[s] = 1;
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            int u = cur.v;
            int d = cur.d;
            dist[s][u] = d;
            for(int v: g[u])
            {
                if(visited[v] == 1)
                    continue;
                visited[v] = 1;
                q.push(State(v, d + 1));
            }
        }
    }
};
