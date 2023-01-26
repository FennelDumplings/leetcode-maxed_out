// prob864: Shortest Path to Get All Keys

/*
 * We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall, "@" is the starting
 * point, ("a", "b", ...) are keys, and ("A", "B", ...) are locks.
 * We start at the starting point, and one move consists of walking one space in one of the 4
 * cardinal directions.  We cannot walk outside the grid, or walk into a wall.  If we walk over a key, we
 * pick it up.  We can't walk over a lock unless we have the corresponding key.
 * For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of the first K letters of the
 * English alphabet in the grid.  This means that there is exactly one key for each lock, and one lock for each key;
 * and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
 * Return the lowest number of moves to acquire all keys.  If it's impossible, return -1.
 */

/*
 * Example 1:
 * Input: ["@.a.#","###.#","b.A.B"]
 * Output: 8
 * Example 2:
 * Input: ["@..aA","..B#.","....b"]
 * Output: 6
 */

/*
 * Note:
 * 1 <= grid.length <= 30
 * 1 <= grid[0].length <= 30
 * grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
 * The number of keys is in [1, 6].  Each key has a different letter and opens exactly one lock.
 */

#include <vector>
#include <string>
#include <queue>

using namespace std;

struct State
{
    int x, y;
    int key_state;
    int step;
    State(int x, int y, int key_state, int step):x(x),y(y),key_state(key_state),step(step){}
};

class Solution {
public:
    // 状态压缩BFS
    int shortestPathAllKeys(vector<string>& grid) {
        // 1 <= k <= 6
        // 111111
        // BFS 过程中，q.pop() 出新点 cur，先 check key_state 是否全1
        // 然后四周点压入 visited[x][y][state] 记录
        int n = grid.size(), m = grid[0].size();
        State start(-1, -1, 0, 0);
        int key_num = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == '@')
                {
                    start.x = i;
                    start.y = j;
                }
                if(grid[i][j] >= 'a' && grid[i][j] <= 'f')
                    ++key_num;
            }
        queue<State> q;
        q.push(start);
        vector<vector<vector<bool> > > visited(n, vector<vector<bool> >(m, vector<bool>((1 << key_num), false)));
        visited[start.x][start.y][0] = true;
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            if(_check(key_num, cur.key_state))
                return cur.step;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d], y = cur.y + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(grid[x][y] == '#') continue;
                if(grid[x][y] >= 'A' && grid[x][y] <= 'F' && !((1 << (grid[x][y] - 'A')) & cur.key_state))
                    continue;
                State nxt(x, y, cur.key_state, cur.step + 1);
                if(grid[x][y] >= 'a' && grid[x][y] <= 'f')
                    nxt.key_state |= (1 << (grid[x][y] - 'a'));
                if(visited[x][y][nxt.key_state]) continue;
                visited[x][y][nxt.key_state] = true;
                q.push(nxt);
            }
        }
        return -1;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool _check(int key_num, int key_state)
    {
        return key_state == ((1 << key_num) - 1);
    }
};
