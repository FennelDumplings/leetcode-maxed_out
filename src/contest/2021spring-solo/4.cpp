
#include <vector>
#include <cstring>
#include <string>

using namespace std;

bool dp[100][50][50][2][2];


class Solution {
public:
    bool escapeMaze(vector<vector<string>>& maze) {
        n = maze[0].size();
        m = maze[0][0].size();
        N = maze.size();
        memset(dp, true, sizeof(bool) * 100 * 50 * 50 * 2 * 2);
        return solve(0, 0, 0, 0, 0, maze);
    }

private:
    int n, m, N;
    int dx[5] = {0, 0, 1, -1, 0};
    int dy[5] = {1, -1, 0, 0, 0};

    bool solve(int i, int x, int y, int a, int b, const vector<vector<string>>& maze)
    {
        // a = 0 未使用第 1 个魔法
        // b = 0 未使用第 2 个魔法
        if(!dp[i][x][y][a][b])
            return false;
        if(x == n - 1 && y == m - 1)
            return true;
        if(m - 1 - x + n - 1 - y > N - i)
            return dp[i][x][y][a][b] = false;
        bool use = false;
        if(maze[i][x][y] == '#')
        {
            if(a == 1 && b == 1)
                return dp[i][x][y][a][b] = false;
            use = true;
        }
        for(int d = 0; d < 5; ++d)
        {
            int next_x = x + dx[d];
            int next_y = y + dy[d];
            if(next_x >= n || next_x < 0 || next_y >= m || next_y < 0)
                continue;
            if(!use)
            {
                if(solve(i + 1, next_x, next_y, a, b, maze))
                    return true;
            }
            else
            {
                if(a == 0)
                {
                    if(solve(i + 1, next_x, next_y, a + 1, b, maze))
                        return true;
                }
                if(b == 0)
                {
                    if(solve(i + 1, next_x, next_y, a, b + 1, maze))
                        return true;
                }
            }
        }
        return dp[i][x][y][a][b] = false;
    }
};
