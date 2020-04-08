// prov1036: Escape a Large Maze

/*
 * In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.
 * We start at the source square and want to reach the target square.  Each move, we can walk to a 4-directionally
 * adjacent square in the grid that isn't in the given list of blocked squares.
 * Return true if and only if it is possible to reach the target square through a sequence of moves.
 */

/*
 * Example 1:
 * Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 * Output: false
 * Explanation:
 * The target square is inaccessible starting from the source square, because we can't walk outside the grid.
 * Example 2:
 * Input: blocked = [], source = [0,0], target = [999999,999999]
 * Output: true
 * Explanation:
 * Because there are no blocked cells, it's possible to reach the target square.
 */

/*
 * Note:
 * 0 <= blocked.length <= 200
 * blocked[i].length == 2
 * 0 <= blocked[i][j] < 10^6
 * source.length == target.length == 2
 * 0 <= source[i][j], target[i][j] < 10^6
 * source != target
 */

#include <vector>

using namespace std;

// 二维离散化
class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {

    }
};

// 有限 BFS, (BFS提前退出)
class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {

    }
};
