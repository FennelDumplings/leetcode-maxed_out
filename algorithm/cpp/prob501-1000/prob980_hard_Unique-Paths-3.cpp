// prob980: Unique Paths III

/*
 * On a 2-dimensional grid, there are 4 types of squares:
 *
 * 1 represents the starting square.  There is exactly one starting square.
 * 2 represents the ending square.  There is exactly one ending square.
 * 0 represents empty squares we can walk over.
 * -1 represents obstacles that we cannot walk over.
 *  Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
 */

/*
 * Example 1:
 * Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
 * Output: 2
 * Explanation: We have the following two paths:
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
 * 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
 * Example 2:
 * Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
 * Output: 4
 * Explanation: We have the following four paths:
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
 * 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
 * 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
 * 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
 * Example 3:
 * Input: [[0,1],[2,0]]
 * Output: 0
 * Explanation:
 * There is no path that walks over every empty square exactly once.
 * Note that the starting and ending square can be anywhere in the grid.
 */

/*
 * Note:
 * 1 <= grid.length * grid[0].length <= 20
 */

#include <vector>
#include <climits>

using namespace std;

// 写成最短路径了
class Solution_2 {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int start_i = -1, start_j = -1;
        int end_i = -1, end_j = -1;
        int end_state = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                {
                    start_i = i;
                    start_j = j;
                }
                if(grid[i][j] == 2)
                {
                    end_i = i;
                    end_j = j;
                }
                if(grid[i][j] == 0)
                    end_state |= (1 << (_ij2idx(i, j, m)));
            }
        // dp[end_i][end_j][end_state]
        // dp[i][j][state] := 位于 i, j，已经经过过 state，的到达 end 的最短路径
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(m, vector<int>(end_state + 1, -2)));
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        visited[end_i][end_j] = true;
        solve(grid, end_i, end_j, end_state, dp, visited);
        return dp[end_i][end_j][end_state];
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int _ij2idx(int i, int j, int m)
    {
        return i * m + j;
    }

    void solve(const vector<vector<int> >& grid, int i, int j, int state, vector<vector<vector<int> > >& dp, vector<vector<bool>>& visited)
    {
        int n = grid.size(), m = grid[0].size();
        if(dp[i][j][state] != -2)
            return;

        if(grid[i][j] == 1 && state == 0)
        {
            dp[i][j][state] = 0;
            return;
        }
        if(grid[i][j] == 1 || state == 0)
        {
            dp[i][j][state] = -1;
            return;
        }

        dp[i][j][state] = INT_MAX;
        int prev_state = state;
        if(grid[i][j] == 0)
            prev_state &= (~(1 << (_ij2idx(i, j, m))));
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m) continue;
            if(grid[x][y] == -1) continue;
            if(visited[x][y]) continue;
            visited[x][y] = true;
            solve(grid, x, y, prev_state, dp, visited);
            if(dp[x][y][prev_state] != -1)
                dp[i][j][state] = min(dp[i][j][state], dp[x][y][prev_state] + 1);
            visited[x][y] = false;
        }
        if(dp[i][j][state] == INT_MAX)
            dp[i][j][state] = -1;
    }
};

// 路径数目
class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int start_i = -1, start_j = -1;
        int end_i = -1, end_j = -1;
        int end_state = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                {
                    start_i = i;
                    start_j = j;
                }
                if(grid[i][j] == 2)
                {
                    end_i = i;
                    end_j = j;
                }
                if(grid[i][j] == 0)
                    end_state |= (1 << (_ij2idx(i, j, m)));
            }
        // dp[end_i][end_j][end_state]
        // dp[i][j][state] := 位于 i, j，已经经过过 state，的到达 end 的路径数目
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(m, vector<int>(end_state + 1, -2)));
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        visited[end_i][end_j] = true;
        solve(grid, end_i, end_j, end_state, dp, visited);
        return dp[end_i][end_j][end_state];
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int _ij2idx(int i, int j, int m)
    {
        return i * m + j;
    }

    void solve(const vector<vector<int> >& grid, int i, int j, int state, vector<vector<vector<int> > >& dp, vector<vector<bool>>& visited)
    {
        int n = grid.size(), m = grid[0].size();
        if(dp[i][j][state] != -2)
            return;

        if(grid[i][j] == 1 && state == 0)
        {
            dp[i][j][state] = 1;
            return;
        }
        if(grid[i][j] == 1 || (grid[i][j] == 0 && state == 0))
        {
            dp[i][j][state] = 0;
            return;
        }

        dp[i][j][state] = 0;
        int prev_state = state;
        if(grid[i][j] == 0)
            prev_state &= (~(1 << (_ij2idx(i, j, m))));
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m) continue;
            if(grid[x][y] == -1) continue;
            if(visited[x][y]) continue;
            visited[x][y] = true;
            solve(grid, x, y, prev_state, dp, visited);
            if(dp[x][y][prev_state] != -1)
                dp[i][j][state] += dp[x][y][prev_state];
            visited[x][y] = false;
        }
    }
};
