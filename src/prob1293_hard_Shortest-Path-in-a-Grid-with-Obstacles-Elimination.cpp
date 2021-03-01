// prob1293: Shortest Path in a Grid with Obstacles Elimination

/*
 * https://leetcode-cn.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
 */

#include <vector>
#include <queue>

using namespace std;

struct State
{
    int i, j;
    int k; // 剩余的删除次数
    int d;
    State(int i, int j, int k, int d):i(i),j(j),k(k),d(d){}
};

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        if(n == 1 && m == 1)
            return 0;
        // (0, 0) -> (n - 1, m - 1)
        queue<State> q;
        q.push(State(0, 0, k, 0));
        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(k + 1, false)));
        visited[0][0][k] = true;
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.i + dx[d], y = cur.j + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(x == n - 1 && y == m - 1)
                    return cur.d + 1;
                if(grid[x][y] == 1)
                {
                    if(cur.k == 0)
                        continue;
                    if(visited[x][y][cur.k - 1])
                        continue;
                    visited[x][y][cur.k - 1] = true;
                    q.push(State(x, y, cur.k - 1, cur.d + 1));
                }
                else
                {
                    if(visited[x][y][cur.k])
                        continue;
                    visited[x][y][cur.k] = true;
                    q.push(State(x, y, cur.k, cur.d + 1));
                }
            }
        }
        return -1;
    }

private:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
};
