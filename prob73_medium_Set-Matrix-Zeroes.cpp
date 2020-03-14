// prob73: Set Matrix Zeroes

/*
 * Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.
 */

/*
 * Example 1:
 * Input:
 * [
 *   [1,1,1],
 *   [1,0,1],
 *   [1,1,1]
 * ]
 * Output:
 * [
 *   [1,0,1],
 *   [0,0,0],
 *   [1,0,1]
 * ]
 * Example 2:
 * Input:
 * [
 *   [0,1,2,0],
 *   [3,4,5,2],
 *   [1,3,1,5]
 * ]
 * Output:
 * [
 *   [0,0,0,0],
 *   [0,4,5,0],
 *   [0,3,1,0]
 * ]
 */

/*
 * Follow up:
 * A straight forward solution using O(mn) space is probably a bad idea.
 * A simple improvement uses O(m + n) space, but still not the best solution.
 * Could you devise a constant space solution?
 */

#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.empty()) return;
        int n = matrix.size(), m = matrix[0].size(); // n 行 m 列
        bool flag_left = false, flag_up = false;
        for(int i = 0; i < n; ++i)
            if(matrix[i][0] == 0)
            {
                flag_left = true;
                break;
            }
        for(int j = 0; j < m; ++j)
            if(matrix[0][j] == 0)
            {
                flag_up = true;
                break;
            }
        for(int i = 1; i < n; ++i)
            for(int j = 1; j < m; ++j)
            {
                if(matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        for(int i = 1; i < n; ++i)
            if(matrix[i][0] == 0)
                for(int j = 1; j < m; ++j)
                    matrix[i][j] = 0;
        for(int j = 1; j < m; ++j)
            if(matrix[0][j] == 0)
                for(int i = 1; i < n; ++i)
                    matrix[i][j] = 0;
        if(flag_left)
            for(int i = 0; i < n; ++i)
                matrix[i][0] = 0;
        if(flag_up)
            for(int j = 0; j < m; ++j)
                matrix[0][j] = 0;
    }
};
