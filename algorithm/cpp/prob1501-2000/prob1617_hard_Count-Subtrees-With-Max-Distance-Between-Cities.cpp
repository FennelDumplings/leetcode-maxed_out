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
        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, 0)));
        vector<vector<int>> g(n); // 建立有根树
        for(const vector<int>& e: edges)
        {
            g[e[0] - 1].push_back(e[1] - 1);
            g[e[1] - 1].push_back(e[0] - 1);
        }
        result.assign(n - 1, 0);
        dfs(0, -1, g);
        return result;
    }

private:
    vector<vector<vector<int>>> dp;
    vector<int> result;
    vector<vector<int>> tmp;

    void dfs(int u, int fa, const vector<vector<int>>& g)
    {
        int n = g.size();
        dp[u][0][0] = 1;
        for(int v: g[u])
            if(v != fa)
            {
                dfs(v, u, g);
                tmp.assign(n, vector<int>(n, 0));
                for(int jf = 0; jf < n; ++jf)
                    for(int kf = jf; kf < n; ++kf)
                    {
                        for(int j = 0; j + kf + 1 < n; ++j)
                            for(int k = j; k < n; ++k)
                            {
                                int deep = max(jf, j + 1);
                                int d = max(max(k, kf), jf + j + 1);
                                tmp[deep][d] += dp[v][j][k] * dp[u][jf][kf];
                            }
                    }
                for(int deep = 1; deep < n; ++deep)
                    for(int d = deep; d < n; ++d)
                    {
                        dp[u][deep][d] += tmp[deep][d];
                        result[d - 1] += tmp[deep][d];
                    }
            }
    }
};
