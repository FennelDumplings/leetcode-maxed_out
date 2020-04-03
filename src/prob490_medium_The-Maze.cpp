// prob490: The Maze

/*
 * There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right,
 * but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
 * Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.
 * The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the
 * borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.
 */

/*
 * Note:
 * There is only one ball and one destination in the maze.
 * Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
 * The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
 * The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int n = maze.size(), m = maze[0].size();
        queue<vector<int> > q; // i, j, d
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        for(int d = 0; d < 4; ++d)
        {
            int x = start[0], y = start[1];
            if(_check(x + dx[d], y + dy[d], n, m, maze))
                q.push({x, y, d});
        }
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        visited[start[0]][start[1]] = true;
        while(!q.empty())
        {
            vector<int> cur = q.front();
            q.pop();
            int i = cur[0], j = cur[1], d = cur[2];
            while(_check(i + dx[d], j + dy[d], n, m, maze))
            {
                i += dx[d];
                j += dy[d];
            }
            if(i == destination[0] && j == destination[1])
                return true;
            if(visited[i][j])
                continue;
            else
                visited[i][j] = true;
            for(int nxt_d = 0; nxt_d < 4; ++nxt_d)
            {
                if((dx[nxt_d] == dx[d] || dy[nxt_d] == dy[d]) || !_check(i + dx[nxt_d], j + dy[nxt_d], n, m, maze))
                    continue;
                q.push({i + dx[nxt_d], j + dy[nxt_d], nxt_d});
            }
        }
        return false;
    }

private:
    bool _check(int i, int j, int n, int m, vector<vector<int> >& maze)
    {
        return i >= 0 && i < n && j >= 0 && j < m && maze[i][j] == 0;
    }
};
