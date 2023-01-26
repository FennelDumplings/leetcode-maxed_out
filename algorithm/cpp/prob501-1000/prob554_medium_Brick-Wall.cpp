// prob554: Brick Wall

/*
 * There is a brick wall in front of you. The wall is rectangular and has several rows of bricks. The bricks have the same height but different width. You want to draw a vertical line from the top to the bottom and cross the least bricks.
 * The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this row from left to right.
 * If your line go through the edge of a brick, then the brick is not considered as crossed. You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.
 * You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.
 */

/*
 * Example:
 * Input: [[1,2,2,1],
 *         [3,1,2],
 *         [1,3,2],
 *         [2,4],
 *         [3,1,2],
 *         [1,3,1,1]]
 *
 * Output: 2
 */

/*
 * Note:
 * The width sum of bricks in different rows are the same and won't exceed INT_MAX.
 * The number of bricks in each row is in range [1,10,000]. The height of wall is in range [1,10,000]. Total number of bricks of the wall won't exceed 20,000.
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int w = 0;
        for(int i: wall[0]) w += i;
        int h = wall.size();
        if(w == 1) return h;
        unordered_map<int, int> blocks; // 1 ~ w - 1 有效
        for(const vector<int>& row: wall)
        {
            int block = 0;
            int n = row.size();
            for(int i = 0; i < n - 1; ++i)
            {
                block += row[i];
                ++blocks[block];
            }
        }
        int max_blocks = 0;
        for(auto block: blocks) max_blocks = max(max_blocks, block.second);
        return h - max_blocks;
    }
};
