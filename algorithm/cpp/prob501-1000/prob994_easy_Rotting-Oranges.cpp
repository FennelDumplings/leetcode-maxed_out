// prob994: Rotting Oranges

/*
 * In a given grid, each cell can have one of three values:
 * the value 0 representing an empty cell;
 * the value 1 representing a fresh orange;
 * the value 2 representing a rotten orange.
 * Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.
 */

/*
 * Example 1:
 * Input: [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 * Example 2:
 * Input: [[2,1,1],[0,1,1],[1,0,1]]
 * Output: -1
 * Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
 * Example 3:
 * Input: [[0,2]]
 * Output: 0
 * Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.
 */

/*
 * Note:
 * 1 <= grid.length <= 10
 * 1 <= grid[0].length <= 10
 * grid[i][j] is only 0, 1, or 2.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        using PII = pair<int, int>;
        int n = grid.size(), m = grid[0].size();
        queue<PII> q;
        int cnt_fresh = 0; // 新鲜的橘子数
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1) ++cnt_fresh;
                else if(grid[i][j] == 2)
                {
                    q.push({i, j});
                }
            }
        if(cnt_fresh == 0) return 0;
        vector<PII> level_nodes;
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        int minutes = 0;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(PII node: level_nodes)
            {
                int i = node.first, j = node.second;
                for(int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d], y = j + dy[d];
                    if(_check(x, y, n, m) && grid[x][y] == 1)
                    {
                        --cnt_fresh;
                        q.push({x, y});
                        grid[x][y] = 2;
                    }
                }
            }
            ++minutes;
        }
        if(cnt_fresh > 0) return -1;
        return minutes - 1;
    }

private:
    bool _check(int i, int j, int n, int m)
    {
        return i >= 0 && i < n && j >= 0 && j < m;
    }
};
