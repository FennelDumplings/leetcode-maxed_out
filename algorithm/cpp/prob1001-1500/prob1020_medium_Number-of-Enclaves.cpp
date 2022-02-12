#include <vector>
#include <queue>

using namespace std;

struct Point
{
    int x, y;
    Point(){}
    Point(int x, int y):x(x),y(y){}
};

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<Point> q;
        for(int i = 0; i < n; ++i)
        {
            if(grid[i][0] == 1)
            {
                visited[i][0] = true;
                q.push(Point(i, 0));
            }
            if(grid[i][m - 1] == 1)
            {
                visited[i][m - 1] = true;
                q.push(Point(i, m - 1));
            }
        }
        for(int j = 1; j < m - 1; ++j)
        {
            if(grid[0][j] == 1)
            {
                visited[0][j] = true;
                q.push(Point(0, j));
            }
            if(grid[n - 1][j] == 1)
            {
                visited[n - 1][j] = true;
                q.push(Point(n - 1, j));
            }
        }
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        while(!q.empty())
        {
            Point cur = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(grid[x][y] == 0)
                    continue;
                if(visited[x][y])
                    continue;
                visited[x][y] = true;
                q.push(Point(x, y));
            }
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1 && !visited[i][j])
                    ans += 1;
            }
        return ans;
    }
};
