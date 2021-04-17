// prob695: Max Area of Island

/*
 * Given a non-empty 2D array grid of 0's and 1's, an island is a
 * group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may
 * assume all four edges of the grid are surrounded by water.
 * Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
 */

/*
 * Example 1:
 * [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 *  [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *  [0,1,1,0,1,0,0,0,0,0,0,0,0],
 *  [0,1,0,0,1,1,0,0,1,0,1,0,0],
 *  [0,1,0,0,1,1,0,0,1,1,1,0,0],
 *  [0,0,0,0,0,0,0,0,0,0,1,0,0],
 *  [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *  [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 * Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
 * Example 2:
 * [[0,0,0,0,0,0,0,0]]
 */

/*
 * Given the above grid, return 0.
 * Note: The length of each dimension in the given grid does not exceed 50.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int result = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 0) continue;
                if(visited[i][j]) continue;
                result = max(result, bfs(grid, i, j, visited));
            }
        return result;
    }

private:
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    using PII = pair<int, int>;

    int bfs(const vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& visited)
    {
        int n = grid.size(), m = grid[0].size();
        queue<PII> q;
        q.push(PII(i, j));
        visited[i][j] = true;
        int cnt = 0;
        while(!q.empty())
        {
            PII cur = q.front();
            q.pop();
            ++cnt;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.first + dx[d];
                int y = cur.second + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(visited[x][y]) continue;
                if(grid[x][y] == 0) continue;
                visited[x][y] = true;
                q.push(PII(x, y));
            }
        }
        return cnt;
    }
};
