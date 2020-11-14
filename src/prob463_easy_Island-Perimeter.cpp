// prob463: Island Perimeter

/*
 * https://leetcode-cn.com/problems/island-perimeter/
 */

#include <vector>
#include <queue>

using namespace std;

struct Point
{
    int x, y;
    Point(int x, int y):x(x),y(y){}
};

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int sx = -1, sy = -1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                {
                    sx = i;
                    sy = j;
                    break;
                }
            }
        queue<Point> q;
        q.push(Point(sx, sy));
        int ans = 0;
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        visited[sx][sy] = true;
        while(!q.empty())
        {
            Point cur = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                {
                    ++ans;
                    continue;
                }
                if(grid[x][y] == 0)
                {
                    ++ans;
                    continue;
                }
                if(visited[x][y])
                    continue;
                visited[x][y] = true;
                q.push(Point(x, y));
            }
        }
        return ans;
    }
};
