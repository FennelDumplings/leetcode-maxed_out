// prob1263: Minimum Moves to Move a Box to Their Target Location

/*
 * https://leetcode-cn.com/problems/minimum-moves-to-move-a-box-to-their-target-location/
 */

#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct State
{
    int x, y, bx, by;
    int d;
    State(int x, int y, int bx, int by, int d):x(x),y(y),bx(bx),by(by),d(d){}
    bool operator<(const State& s) const
    {
        return d > s.d;
    }
};

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // 起始状态
        State state(-1, -1, -1, -1, 0);
        int ex = -1, ey = -1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 'B')
                {
                    state.bx = i;
                    state.by = j;
                }
                if(grid[i][j] == 'S')
                {
                    state.x = i;
                    state.y = j;
                }
                if(grid[i][j]== 'T')
                {
                    ex = i;
                    ey = j;
                }
            }

        memset(dist, -1, sizeof(dist));
        priority_queue<State> q;
        q.push(state);
        dist[state.x][state.y][state.bx][state.by] = 0;
        while(!q.empty())
        {
            State cur = q.top();
            q.pop();
            if(cur.bx == ex && cur.by == ey)
                return dist[cur.x][cur.y][ex][ey];
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(x >= n || x < 0 || y >= m || y < 0)
                    continue;
                if(grid[x][y] == '#')
                    continue;
                if(x == cur.bx && y == cur.by)
                {
                    // 箱子的下一个位置
                    int bx = cur.bx + dx[d];
                    int by = cur.by + dy[d];
                    if(bx < 0 || bx >= n || by < 0  || by >= m)
                        continue;
                    if(grid[bx][by] == '#')
                        continue;
                    if(dist[x][y][bx][by] == -1 || dist[x][y][bx][by] > cur.d + 1)
                    {
                        dist[x][y][bx][by] = cur.d + 1;
                        q.push(State(x, y, bx, by, cur.d + 1));
                    }
                }
                else
                {
                    if(dist[x][y][cur.bx][cur.by] == -1 || dist[x][y][cur.bx][cur.by] > cur.d)
                    {
                        dist[x][y][cur.bx][cur.by] = cur.d;
                        q.push(State(x, y, cur.bx, cur.by, cur.d));
                    }
                }
            }
        }
        return -1;
    }

private:
    int dist[21][21][21][21];
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
};

// 双端队列：对 d 有贡献的状态从头进入，对 d 没有贡献的从尾进入
#include <deque>

class Solution_2 {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // 起始状态
        State state(-1, -1, -1, -1, 0);
        int ex = -1, ey = -1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 'B')
                {
                    state.bx = i;
                    state.by = j;
                }
                if(grid[i][j] == 'S')
                {
                    state.x = i;
                    state.y = j;
                }
                if(grid[i][j]== 'T')
                {
                    ex = i;
                    ey = j;
                }
            }

        memset(dist, -1, sizeof(dist));
        deque<State> q;
        q.push_back(state);
        dist[state.x][state.y][state.bx][state.by] = 0;
        while(!q.empty())
        {
            State cur = q.front();
            q.pop_front();
            if(cur.bx == ex && cur.by == ey)
                return dist[cur.x][cur.y][ex][ey];
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(x >= n || x < 0 || y >= m || y < 0)
                    continue;
                if(grid[x][y] == '#')
                    continue;
                if(x == cur.bx && y == cur.by)
                {
                    // 箱子的下一个位置
                    int bx = cur.bx + dx[d];
                    int by = cur.by + dy[d];
                    if(bx < 0 || bx >= n || by < 0  || by >= m)
                        continue;
                    if(grid[bx][by] == '#')
                        continue;
                    if(dist[x][y][bx][by] == -1 || dist[x][y][bx][by] > cur.d + 1)
                    {
                        dist[x][y][bx][by] = cur.d + 1;
                        q.push_back(State(x, y, bx, by, cur.d + 1));
                    }
                }
                else
                {
                    if(dist[x][y][cur.bx][cur.by] == -1 || dist[x][y][cur.bx][cur.by] > cur.d)
                    {
                        dist[x][y][cur.bx][cur.by] = cur.d;
                        q.push_front(State(x, y, cur.bx, cur.by, cur.d));
                    }
                }
            }
        }
        return -1;
    }

private:
    int dist[21][21][21][21];
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
};
