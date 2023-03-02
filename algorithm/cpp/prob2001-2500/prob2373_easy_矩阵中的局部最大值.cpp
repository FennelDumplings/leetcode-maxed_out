class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> result(n - 2, vector<int>(m - 2, 0));
        for(int i = 0; i < n - 2; ++i)
            for(int j = 0; j < m - 2; ++j)
            {
                int max_x = grid[i][j];
                for(int x = i; x <= i + 2; ++x)
                    for(int y = j; y <= j + 2; ++y)
                        max_x = max(max_x, grid[x][y]);
                result[i][j] = max_x;
            }
        return result;
    }
};
