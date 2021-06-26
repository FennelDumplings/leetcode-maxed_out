// prob576: Out of Boundary Paths

/*
 * There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball,
 * you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right).
 * However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary.
 * The answer may be very large, return it after mod 109 + 7.
 */

/*
 * Note:
 * Once you move the ball out of boundary, you cannot move it back.
 * The length and height of the grid is in range [1,50].
 * N is in range [0,50].
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        if(N == 0) return 0;
        // i, j, k: m, n, N
        vector<vector<vector<int> > > dp(m, vector<vector<int> >(n, vector<int>(N + 1, -1)));
        return dfs(i, j, m, n, N, dp);
    }

private:
    int MOD = 1e9 + 7;

    int dfs(int i, int j, int m, int n, int k, vector<vector<vector<int> > >& dp)
    {
        if(i < 0 || i >= m || j < 0 || j >= n)
            return 1;
        if(k == 0)
            return 0;
        if(dp[i][j][k] != -1)
            return dp[i][j][k];

        dp[i][j][k] = 0;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            dp[i][j][k] = (dp[i][j][k] + dfs(x, y, m, n, k - 1, dp)) % MOD;
        }
        return dp[i][j][k];
    }
};
