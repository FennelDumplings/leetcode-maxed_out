// prob499: The Maze III

/*
 * There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by
 * rolling up (u), down (d), left (l) or right (r), but it won't stop rolling until hitting a wall.
 * When the ball stops, it could choose the next direction. There is also a hole in this maze.
 * The ball will drop into the hole if it rolls on to the hole.
 * Given the ball position, the hole position and the maze, find out how the ball could drop into the hole by moving the shortest distance.
 * The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the hole (included).
 * Output the moving directions by using 'u', 'd', 'l' and 'r'. Since there could be several different shortest ways, you
 * should output the lexicographically smallest way. If the ball cannot reach the hole, output "impossible".
 * The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the
 * borders of the maze are all walls. The ball and the hole coordinates are represented by row and column indexes.
 */

/*
 * Example 1:
 * Input 1: a maze represented by a 2D array
 * 0 0 0 0 0
 * 1 1 0 0 1
 * 0 0 0 0 0
 * 0 1 0 0 1
 * 0 1 0 0 0
 * Input 2: ball coordinate (rowBall, colBall) = (4, 3)
 * Input 3: hole coordinate (rowHole, colHole) = (0, 1)
 * Output: "lul"
 */

/*
 * Example 2:
 * Input 1: a maze represented by a 2D array
 * 0 0 0 0 0
 * 1 1 0 0 1
 * 0 0 0 0 0
 * 0 1 0 0 1
 * 0 1 0 0 0
 * Input 2: ball coordinate (rowBall, colBall) = (4, 3)
 * Input 3: hole coordinate (rowHole, colHole) = (3, 0)
 * Output: "impossible"
 * Explanation: The ball cannot reach the hole.
 */

/*
 * Note:
 * There is only one ball and one hole in the maze.
 * Both the ball and hole exist on an empty space, and they will not be at the same position initially.
 * The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
 * The maze contains at least 2 empty spaces, and the width and the height of the maze won't exceed 30.
 */

#include <vector>
#include <string>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        int n = maze.size(), m = maze[0].size();
        int dx[4] = {1, 0, 0, -1};
        int dy[4] = {0, -1, 1, 0};
        vector<char> mapping({'d', 'l', 'r', 'u'});
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        priority_queue<State, vector<State>, Cmp> pq;
        pq.push(State(ball[0], ball[1], 0, ""));
        string result = "#";
        int min_len = INT_MAX;
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(visited[cur.i][cur.j]) continue;
            visited[cur.i][cur.j] = true;
            for(int d = 0; d < 4; ++d)
            {
                int i = cur.i, j = cur.j, len = cur.len;
                string d_seq = cur.d_seq + mapping[d];
                while(_check(i + dx[d], j + dy[d], n, m, maze))
                {
                    i += dx[d];
                    j += dy[d];
                    ++len;
                    if(vector<int>({i, j}) == hole)
                    {
                        if(len < min_len)
                        {
                            min_len = len;
                            result = d_seq;
                        }
                        else if(len == min_len)
                            result = min(result, d_seq);
                    }
                }
                if(!visited[i][j])
                    pq.push(State(i, j, len, d_seq));
            }
        }
        return result == "#" ? "impossible" : result;
    }

private:
    struct State
    {
        int i, j, len;
        string d_seq;
        State(int x, int y, int l, string s):i(x),j(y),len(l),d_seq(s){}
    };

    struct Cmp
    {
        bool operator() (const State& state1, const State& state2)
        {
            if(state1.len == state2.len)
                return state1.d_seq > state2.d_seq;
            return state1.len > state2.len;
        }
    };

    bool _check(int i, int j, int n, int m, vector<vector<int> >& maze)
    {
        return i >= 0 && i < n && j >= 0 && j < m && maze[i][j] == 0;
    }
};

