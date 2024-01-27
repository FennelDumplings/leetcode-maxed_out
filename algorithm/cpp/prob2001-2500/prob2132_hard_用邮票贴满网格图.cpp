class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> sums(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                sums[i][j] = grid[i - 1][j - 1] + sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];

        vector<vector<int>> diff(n + 1, vector<int>(m + 1));
        for(int i = 0; i <= n - stampHeight; ++i)
            for(int j = 0; j <= m - stampWidth; ++j)
            {
                int x1 = i;
                int y1 = j;
                int x2 = i + stampHeight - 1;
                int y2 = j + stampWidth - 1;
                if(sums[x2 + 1][y2 + 1] - sums[x2 + 1][y1] - sums[x1][y2 + 1] + sums[x1][y1] == 0)
                {
                    diff[x1][y1] += 1;
                    diff[x2 + 1][y1] -= 1;
                    diff[x1][y2 + 1] -= 1;
                    diff[x2 + 1][y2 + 1] += 1;
                }
            }

        vector<vector<int>> visited(n + 1, vector<int>(m + 1));
        visited[0][0] = diff[0][0];
        for(int i = 1; i <= n; ++i)
            visited[i][0] = diff[i][0] + visited[i - 1][0];
        for(int j = 1; j <= m; ++j)
            visited[0][j] = diff[0][j] + visited[0][j - 1];
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                visited[i][j] = diff[i][j] + visited[i][j - 1] + visited[i - 1][j] - visited[i - 1][i - 1];
            }

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 0 && visited[i][j] == 0)
                    return false;
            }
        return true;
    }
};
