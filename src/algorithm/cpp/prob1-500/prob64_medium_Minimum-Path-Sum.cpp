// prob64: Minimum Path Sum

/*
 * Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
 * Note: You can only move either down or right at any point in time.
 */

/*
 * Example:
 * Input:
 * [
 *   [1,3,1],
 *   [1,5,1],
 *   [4,2,1]
 * ]
 * Output: 7
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int> > dp(m, vector<int>(n, INT_MAX));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(i == 0 && j == 0) dp[i][j] = 0;
                if(i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                if(j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1]);
                dp[i][j] += grid[i][j];
            }
        return dp[m - 1][n - 1];
    }
};
