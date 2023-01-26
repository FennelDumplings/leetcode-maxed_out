/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 */

#include <unordered_set>

using namespace std;

class Robot {
  public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    bool move();

    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    void turnLeft();
    void turnRight();

    // Clean the current cell.
    void clean();
};

class Solution {
public:
    void cleanRoom(Robot& robot) {
        dfs(robot, 0, 0, 0);
    }

private:
    unordered_set<int> setting;
    const int p = 21101;
    const int MOD = 1e9 + 7;
    using ll = long long;
    int hash(int x, int y)
    {
        return ((ll)x * p + y) % MOD;
    }
    /*
     * ori:
     *  0: 上
     *  1: 左
     *  2: 下
     *  3: 右
     */
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    void dfs(Robot& robot, int x, int y, int ori)
    {
        robot.clean();
        setting.insert(hash(x, y));
        for(int d = 0; d < 4; ++d)
        {
            int nxt_x = x + dx[ori];
            int nxt_y = y + dy[ori];
            if(setting.count(hash(nxt_x, nxt_y)) == 0 && robot.move())
            {
                dfs(robot, nxt_x, nxt_y, ori);
                robot.turnRight();
            }
            else
                robot.turnLeft();
            ori = (ori + 1) % 4;
        }
        robot.turnLeft();
        robot.turnLeft();
        robot.move();
    }
};
