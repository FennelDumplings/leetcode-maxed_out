// prob286: Walls and Gates

/*
 * You are given a m x n 2D grid initialized with these three possible values.
 * -1 - A wall or an obstacle.
 *  0 - A gate.
 *  INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
 *  Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.
 */

/*
 * Example: 
 * Given the 2D grid:
 * INF  -1  0  INF
 * INF INF INF  -1
 * INF  -1 INF  -1
 *   0  -1 INF INF
 * After running your function, the 2D grid should be:
 *   3  -1   0   1
 *   2   2   1  -1
 *   1  -1   2  -1
 *   0  -1   3   4
 */

#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct State
{
    int i, j, d;
    State(int i, int j, int d):i(i),j(j),d(d){}
};

class Solution {
public:
    // -1: 墙
    // 0: 门
    // INT_MAX: 房
    void wallsAndGates(vector<vector<int>>& rooms) {
        if(rooms.empty()) return;
        int n = rooms.size(), m = rooms[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<State> q;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(rooms[i][j] == 0)
                {
                    visited[i][j] = true;
                    q.push(State(i, j, 0));
                }
            }
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            rooms[cur.i][cur.j] = cur.d;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.i + dx[d], y = cur.j + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(rooms[x][y] == -1)
                    continue;
                if(visited[x][y])
                    continue;
                visited[x][y] = true;
                q.push(State(x, y, cur.d + 1));
            }
        }
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
};
