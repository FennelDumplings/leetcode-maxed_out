// prob62: Unique Paths

/*
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 *
 * The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 *
 * How many possible unique paths are there?
 */

/*
 * Example 1:
 * Input: m = 3, n = 2
 * Output: 3
 * Example 2:
 * Input: m = 7, n = 3
 * Output: 28
 */

/*
 * Constraints:
 * 1 <= m, n <= 100
 * It's guaranteed that the answer will be less than or equal to 2 * 10 ^ 9.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int> > dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(i > 0) dp[i][j] += dp[i - 1][j];
                if(j > 0) dp[i][j] += dp[i][j - 1];
            }
        return dp[m - 1][n - 1];
    }
};
