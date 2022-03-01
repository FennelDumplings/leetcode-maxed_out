#include <unordered_set>
#include <vector>

class Solution {
public:
    int domino(int n, int m, vector<vector<int>>& broken) {
        int n_broken = broken.size();
        vector<vector<int>> g(n * m);
        unordered_set<int> setting;
        for(const vector<int>& b: broken)
            setting.insert(key(b[0], b[1], n));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int u = key(i, j, n);
                if(setting.count(u) > 0)
                    continue;
                for(int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if(x < 0 || x >= n || y < 0 || y >= m)
                        continue;
                    int v = key(x, y, n);
                    g[u].push_back(v);
                    g[v].push_back(u);
                }
            }
        int ans = 0;
        vector<bool> visited;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int u = key(i, j, n);
                if(setting.count(u) > 0)
                    continue;
                visited.assign(n * m, false);
                if(dfs(u, g, visited))
                    ++ans;
            }
        return ans;
    }

    bool dfs(const vector<vector<int>>& g, vector<bool>& visited, int u)
    {
        //
    }

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    int key(int x, int y, int n)
    {
        return x * n + y;
    }

};
