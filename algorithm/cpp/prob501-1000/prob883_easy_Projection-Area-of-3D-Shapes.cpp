// prob883: Projection Area of 3D Shapes

/*
 * On a N * N grid, we place some 1 * 1 * 1 cubes that are axis-aligned with the x, y, and z axes.
 * Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).
 * Now we view the projection of these cubes onto the xy, yz, and zx planes.
 * A projection is like a shadow, that maps our 3 dimensional figure to a 2 dimensional plane. 
 * Here, we are viewing the "shadow" when looking at the cubes from the top, the front, and the side.
 * Return the total area of all three projections.
 */

/*
 * Example 1:
 * Input: [[2]]
 * Output: 5
 * Example 2:
 * Input: [[1,2],[3,4]]
 * Output: 17
 * Explanation:
 * Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
 * Example 3:
 * Input: [[1,0],[0,2]]
 * Output: 8
 * Example 4:
 * Input: [[1,1,1],[1,0,1],[1,1,1]]
 * Output: 14
 * Example 5:
 * Input: [[2,2,2],[2,1,2],[2,2,2]]
 * Output: 21
 */

/*
 * Note:
 * 1 <= grid.length = grid[0].length <= 50
 * 0 <= grid[i][j] <= 50
 */

#include <vector>

using namespace std;

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<int> max_y(n, 0); // max_y[i] 为第 i 行上各列最大值
        vector<int> max_x(m, 0); // max_x[j] 为第 j 列上各行最大值
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 0) continue;
                max_y[i] = max(max_y[i], grid[i][j]);
                max_x[j] = max(max_x[j], grid[i][j]);
                ++result;
            }
        }
        for(int i: max_x) result += i;
        for(int i: max_y) result += i;
        return result;
    }
};
