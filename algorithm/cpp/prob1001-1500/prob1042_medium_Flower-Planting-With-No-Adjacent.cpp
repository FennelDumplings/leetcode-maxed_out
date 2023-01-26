// prob1042: Flower Planting With No Adjacent

/*
 * https://leetcode-cn.com/problems/flower-planting-with-no-adjacent/
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        vector<vector<int>> g(n + 1);
        for(vector<int>& e: paths)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<int> color(n, -1);
        for(int i = 1; i <= n; ++i)
        {
            if(color[i - 1] != -1) continue;
            dfs(g, i, color);
        }
        return color;
    }

private:
    void dfs(const vector<vector<int>>& g, int u, vector<int>& color)
    {
        vector<bool> setting(5, false);
        for(int v: g[u])
        {
            if(color[v - 1] != -1)
                setting[color[v - 1]] = true;
        }
        for(int i = 1; i <= 4; ++i)
            if(!setting[i])
                color[u - 1] = i;
        for(int v: g[u])
        {
            if(color[v - 1] != -1)
                continue;
            dfs(g, v, color);
        }
    }
};
