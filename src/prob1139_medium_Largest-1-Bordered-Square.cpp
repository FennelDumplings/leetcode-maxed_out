// prob1139: Largest 1-Bordered Square

/*
 * https://leetcode-cn.com/problems/largest-1-bordered-square/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> col_sums(m, vector<int>(n + 1));
        vector<vector<int>> row_sums(n, vector<int>(m + 1));
        for(int i = 0; i < n; ++i)
            for(int j = 1; j <= m; ++j)
                row_sums[i][j] = row_sums[i][j - 1] + grid[i][j - 1];
        for(int j = 0; j < m; ++j)
            for(int i = 1; i <= n; ++i)
                col_sums[j][i] = col_sums[j][i - 1] + grid[i - 1][j];
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                for(int l = ans + 1; l <= min(i + 1, j + 1); ++l)
                {
                    if(row_sums[i][j + 1] - row_sums[i][j + 1 - l] != l
                       || row_sums[i + 1 - l][j + 1] - row_sums[i + 1 - l][j + 1 - l] != l
                       || col_sums[j][i + 1] - col_sums[j][i + 1 - l] != l
                       || col_sums[j + 1 - l][i + 1] - col_sums[j + 1 - l][i + 1 - l] != l
                       )
                        continue;
                    ans = l;
                }
            }
        return ans * ans;
    }
};
