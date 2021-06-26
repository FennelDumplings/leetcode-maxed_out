// prob1191: Shortest Path in Binary Matrix

/*
 * In an N by N square grid, each cell is either empty (0) or blocked (1).
 * A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:
 * Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
 * C_1 is at location (0, 0) (ie. has value grid[0][0])
 * C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
 * If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
 * Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.
 */

#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class Solution_2 {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int N = grid.size();
        if(N == 1 && grid[0][0] == 0) return 1;
        if(N == 1 && grid[0][0] == 1) return -1;
        if(grid[0][0] == 1) return -1;

        vector<vector<bool> > visited(N, vector<bool>(N, false));
        queue<PII> q;
        q.push(PII(0, 0));
        visited[0][0] = true;
        int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
        int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

        vector<PII> level_nodes;
        int result = 0;
        bool get_end = false;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(PII point: level_nodes)
            {
                if(point.first == N - 1 && point.second == N - 1)
                {
                    get_end = true;
                    break;
                }
                for(int d = 0; d < 8; ++d)
                {
                    PII nxt(point.first + dx[d], point.second + dy[d]);
                    if(_check(nxt, grid, visited))
                    {
                        q.push(nxt);
                        visited[nxt.first][nxt.second] = true;
                    }
                }
            }
            ++result;
            if(get_end)
                return result;
        }
        return -1;
    }

private:
    using PII = pair<int, int>;

    bool _check(const PII& nxt, const vector<vector<int> >& grid, vector<vector<bool> >& visited)
    {
        int N = grid.size();
        if(nxt.first < 0 || nxt.first >= N || nxt.second < 0 || nxt.second >= N) return false;
        return (!visited[nxt.first][nxt.second]) && (grid[nxt.first][nxt.second] == 0);
    }
};

// Astar
struct State
{
    int x, y;
    int d;
    int h;
    State(int x, int y, int d, int h):x(x),y(y),d(d),h(h){}
};

struct Cmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.d + s1.h > s2.d + s2.h;
    }
};

class Solution_2 {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int N = grid.size();
        if(N == 1 && grid[0][0] == 0) return 1;
        if(N == 1 && grid[0][0] == 1) return -1;
        if(grid[0][0] == 1) return -1;
        // N * N
        State s(0, 0, 1, h(0, 0, N - 1, N - 1));
        return bfs(grid, s, N - 1, N - 1);
    }

private:
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

    int bfs(const vector<vector<int>>& grid, State s, int tx, int ty)
    {
        priority_queue<State, vector<State>, Cmp> pq;
        pq.push(s);
        int N = grid.size();
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(cur.x == tx && cur.y == ty)
                return cur.d;
            if(visited[cur.x][cur.y])
                continue;
            visited[cur.x][cur.y] = true;
            for(int d = 0; d < 8; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(x < 0 || x >= N || y < 0 || y >= N)
                    continue;
                if(grid[x][y] != 0)
                    continue;
                if(visited[x][y])
                    continue;
                State nxt(x, y, cur.d + 1, h(x, y, tx, ty));
                pq.push(nxt);
            }
        }
        return -1;
    }

    int h(int x, int y, int tx, int ty)
    {
        return max(abs(tx - x), abs(y - ty));
    }
};

// IDAstar

#include <cstring>

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int N = grid.size();
        if(N == 1 && grid[0][0] == 0) return 1;
        if(N == 1 && grid[0][0] == 1) return -1;
        if(grid[0][0] == 1) return -1;
        int max_depth = N * N;
        int depth = 1;
        bool **visited = new bool*[N];
        for(int i = 0; i < N; ++i)
            visited[i] = new bool[N];
        for(int i = 0; i < N; ++i)
            memset(visited[i], false, N * sizeof(bool));

        while(depth <= max_depth && !dfs(grid, 0, 0, N - 1, N - 1, 1, depth, visited))
        {
            for(int i = 0; i < N; ++i)
                memset(visited[i], false, N * sizeof(bool));
            ++depth;
            visited[0][0] = true;
        }
        if(depth > max_depth)
            return -1;
        return depth;
    }

private:
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

    bool dfs(const vector<vector<int>>& grid, int i, int j, int tx, int ty, int depth, const int max_depth, bool** visited)
    {
        if(depth + h(i, j, tx, ty) > max_depth)
            return false;
        if(i == tx && j == ty)
            return true;
        int N = grid.size();
        for(int d = 0; d < 8; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x < 0 || x >= N || y < 0 || y >= N)
                continue;
            if(grid[x][y] != 0)
                continue;
            if(visited[x][y])
                continue;
            visited[x][y] = true;
            if(dfs(grid, x, y, tx, ty, depth + 1, max_depth, visited))
                return true;
            visited[x][y] = true;
        }
        return false;
    }

    int h(int x, int y, int tx, int ty)
    {
        return max(abs(tx - x), abs(y - ty));
    }
};
