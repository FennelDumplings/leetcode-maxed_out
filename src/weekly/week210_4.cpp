
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

class Solution {
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
