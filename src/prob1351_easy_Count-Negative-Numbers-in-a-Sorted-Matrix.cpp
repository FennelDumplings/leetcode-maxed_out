// prob1351: Count Negative Numbers in a Sorted Matrix

/*
 * Given a m * n matrix grid which is sorted in non-increasing order both row-wise and column-wise. 
 * Return the number of negative numbers in grid.
 */

/*
 * Example 1:
 * Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
 * Output: 8
 * Explanation: There are 8 negatives number in the matrix.
 * Example 2:
 * Input: grid = [[3,2],[1,0]]
 * Output: 0
 * Example 3:
 * Input: grid = [[1,-1],[-1,-1]]
 * Output: 3
 * Example 4:
 * Input: grid = [[-1]]
 * Output: 1
 */

/*
 * Constraints:
 *
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 100
 * -100 <= grid[i][j] <= 100
 */

#include <vector>

using namespace std;

struct Point
{
    int i, j;
    Point(int i, int j):i(i),j(j){}
};

class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        Point iter(0, n - 1);
        int result = 0;
        while(iter.i < m && iter.j >= 0)
        {
            if(grid[iter.i][iter.j] >= 0)
                ++iter.i;
            else
            {
                result += m - iter.i;
                --iter.j;
            }
        }
        return result;
    }
};
