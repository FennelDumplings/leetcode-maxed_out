#include <vector>

using namespace std;

class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        // dp[i][j] := 以 (i, j) 为终点的严格递增路径条数
        dp = vector<vector<int>>(n, vector<int>(m, -1));
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                ans = ((ll)ans + dfs(i, j, grid)) % MOD;
        return ans;
    }

    int n, m;
    vector<vector<int>> dp;
    using ll = long long;
    const int MOD = 1e9 + 7;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    int dfs(int i, int j, const vector<vector<int>>& grid)
    {
        if(dp[i][j] != -1)
            return dp[i][j];
        dp[i][j] = 1;
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(grid[x][y] >= grid[i][j])
                continue;
            dp[i][j] = ((ll)dp[i][j] + dfs(x, y, grid)) % MOD;
        }
        return dp[i][j];
    }
};

