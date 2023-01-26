// prob874: Walking Robot Simulation

/*
 * A robot on an infinite grid starts at point (0, 0) and faces north.  The robot can receive one of three possible types of commands:
 * -2: turn left 90 degrees
 *  -1: turn right 90 degrees
 *  1 <= x <= 9: move forward x units
 *  Some of the grid squares are obstacles. 
 *  The i-th obstacle is at grid point (obstacles[i][0], obstacles[i][1])
 *  If the robot would try to move onto them, the robot stays on the previous grid square instead (but still continues following the rest of the route.)
 *  Return the square of the maximum Euclidean distance that the robot will be from the origin.
 */

/*
 * Example 1:
 * Input: commands = [4,-1,3], obstacles = []
 * Output: 25
 * Explanation: robot will go to (3, 4)
 * Example 2:
 * Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
 * Output: 65
 * Explanation: robot will be stuck at (1, 4) before turning left and going to (1, 8)
 */

/*
 * Note:
 * 0 <= commands.length <= 10000
 * 0 <= obstacles.length <= 10000
 * -30000 <= obstacle[i][0] <= 30000
 *  -30000 <= obstacle[i][1] <= 30000
 *  The answer is guaranteed to be less than 2 ^ 31.
 */

#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int i = 0, j = 0, d = 1;
        unordered_map<int, set<int>> o_row; // 各行中的障碍
        unordered_map<int, set<int>> o_col; // 各列中的障碍
        for(const vector<int>& o: obstacles)
        {
            int row = o[0], col = o[1];
            o_row[row].insert(col);
            o_col[col].insert(row);
        }
        int result = 0;
        for(int command: commands)
        {
            if(command < 0)
            {
                d = get_direct(d, command);
                continue;
            }
            int l = command; // 前移 l
            // d
            // 0 : i, j -> i + l * dx, j   [i + l * dx .. i][j]
            // 1 : i, j -> i, j + l * dy   [i][j .. j + l * dy]
            // 2 : i, j -> i + l * dx, j   [i .. i + l * dx][j]
            // 3 : i, j -> i, j + l * dy   [i][j + l * dy .. j]
            if(d == 0)
            {
                // o_col[j] 中小于 i 的第一个障碍
                auto it = o_col[j].lower_bound(i); // >= i 的第一个位置 --it 是小于 i 的最大数
                if(it == o_col[j].begin())
                    i = i + l * dx[d];
                else
                {
                    --it;
                    i = max(*it + 1, i + l * dx[d]);
                }
            }
            else if(d == 1)
            {
                // o_row[i] 中大于 j 的第一个障碍
                auto it = o_row[i].upper_bound(j); // > j 的第一个位置
                if(it == o_row[i].end())
                    j = j + l * dy[d];
                else
                    j = min(*it - 1, j + l * dy[d]);
            }
            else if(d == 2)
            {
                // o_col[j] 中大于 i 的第一个障碍
                auto it = o_col[j].upper_bound(i); // > i 的第一个位置
                if(it == o_col[j].end())
                    i = i + l * dx[d];
                else
                    i = min(*it - 1, i + l * dx[d]);
            }
            else
            {
                // o_row[i] 中小于 j 的第一个障碍
                auto it = o_row[i].lower_bound(j); // >= j 的第一个位置 --it 是小于 j 的最大数
                if(it == o_row[i].begin())
                    j = j + l * dy[d];
                else
                {
                    --it;
                    j = max(*it + 1, j + l * dy[d]);
                }
            }
            result = max(result, i * i + j * j);
        }
        return result;
    }

private:
    // 0 : 上
    // 1 : 右
    // 2 : 下
    // 3 : 左
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int get_direct(int d, int command)
    {
        if(command == -1)
            return (d + 1) % 4;
        else
            return (d + 3) % 4;
    }
};
