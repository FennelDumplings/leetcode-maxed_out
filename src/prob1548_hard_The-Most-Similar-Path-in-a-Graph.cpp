// prob1548: The Most Similar Path in a Graph

/*
 * https://leetcode-cn.com/problems/the-most-similar-path-in-a-graph/
 */

#include <vector>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        vector<vector<int>> g(n);
        for(vector<int> &e: roads)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        int m = targetPath.size();
        vector<vector<int>> ed(n, vector<int>(m, -1));
        for(int v = 0; v < n; ++v)
        {
            for(int i = 0; i < m; ++i)
                ed[v][i] = names[v] != targetPath[i];
        }
        vector<vector<int>> dp(n, vector<int>(m + 1, INT_MAX / 2));
        for(int v = 0; v < n; ++v)
            dp[v][0] = ed[v][0];
        for(int i = 1; i < m; ++i)
            for(int v = 0; v < n; ++v)
            {
                for(int u: g[v])
                    dp[v][i] = min(dp[v][i], ed[v][i] + dp[u][i - 1]);
            }
        int end = -1;
        int min_ed = INT_MAX / 2;
        for(int v = 0; v < n; ++v)
        {
            if(dp[v][m - 1] < min_ed)
            {
                end = v;
                min_ed = dp[v][m - 1];
            }
        }
        vector<int> result(m);
        result[m - 1] = end;
        int next = end;
        for(int i = m - 2; i >= 0; --i)
        {
            int u = -1;
            for(int v: g[next])
                if(dp[v][i] == dp[next][i + 1] - ed[next][i + 1])
                {
                    u = v;
                    break;
                }
            result[i] = u;
            next = u;
        }
        return result;
    }
};
