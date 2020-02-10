// prob74: Search a 2D Matrix

/*
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of the previous row.
 */

/*
 *Example 1:
 * Input:
 * matrix = [
 *   [1,   3,  5,  7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 50]
 * ]
 * target = 3
 * Output: true
 * Example 2:
 * Input:
 * matrix = [
 *   [1,   3,  5,  7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 50]
 * ]
 * target = 13
 * Output: false
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int m = matrix.size();
        int n = matrix[0].size();
        int left = 0, right = m * n;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            pair<int, int> xy = convert_2dto1d(mid, n);
            int x = xy.first, y = xy.second;
            if(matrix[x][y] == target)
                return true;
            else if(matrix[x][y] < target)
                left = mid + 1;
            else
                right = mid;
        }
        return false;
    }

private:
    pair<int, int> convert_2dto1d(int mid, int n)
    {
        int x, y;
        x = mid / n;
        y = mid % n;
        return pair<int, int>(x, y);
    }
};
