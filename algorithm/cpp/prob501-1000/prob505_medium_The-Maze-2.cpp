// prob505: The Maze II

/*
 * There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right,
 * but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
 * Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination.
 * The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included).
 * If the ball cannot stop at the destination, return -1.
 * The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of
 * the maze are all walls. The start and destination coordinates are represented by row and column indexes.
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
#include <climits>

using namespace std;

// 带权 BFS
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int n = maze.size(), m = maze[0].size();
        int dx[4] = {1, 0, 0, -1};
        int dy[4] = {0, -1, 1, 0};
        priority_queue<vector<int>, vector<vector<int> >, Cmp> pq; // len, i, j
        pq.push({start[0], start[1], 0});
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        while(!pq.empty())
        {
            vector<int> cur = pq.top();
            pq.pop();
            if(vector<int>({cur[0], cur[1]}) == destination)
                return cur[2];
            if(visited[cur[0]][cur[1]]) continue;
            visited[cur[0]][cur[1]] = true;
            for(int d = 0; d < 4; ++d)
            {
                int i = cur[0], j = cur[1], len = cur[2];
                while(_check(i + dx[d], j + dy[d], n, m, maze))
                {
                    i += dx[d];
                    j += dy[d];
                    ++len;
                }
                if(!visited[i][j])
                    pq.push({i, j, len});
            }
        }
        return -1;
    }

private:
    struct Cmp
    {
        bool operator() (const vector<int>& item1, const vector<int>& item2)
        {
            if(item1[2] == item2[2])
                return item1 > item2;
            return item1[2] > item2[2];
        }
    };

    bool _check(int i, int j, int n, int m, const vector<vector<int> >& maze)
    {
        return i >= 0 && i < n && j >= 0 && j < m && maze[i][j] == 0;
    }
};
