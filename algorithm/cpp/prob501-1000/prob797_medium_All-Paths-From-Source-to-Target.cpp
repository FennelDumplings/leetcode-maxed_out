// prob797: All Paths From Source to Target

/*
 * https://leetcode-cn.com/problems/all-paths-from-source-to-target/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> path(1, 0);
        vector<vector<int>> result;
        dfs(graph, 0, n - 1, result, path);
        return result;
    }

private:
    void dfs(const vector<vector<int>>& g, int u, int t, vector<vector<int>>& result, vector<int>& path)
    {
        if(u == t)
        {
            result.push_back(path);
            return;
        }
        for(int v: g[u])
        {
            path.push_back(v);
            dfs(g, v, t, result, path);
            path.pop_back();
        }
    }
};
