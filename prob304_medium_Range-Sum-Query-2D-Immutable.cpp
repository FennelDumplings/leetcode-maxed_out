// prob304: Range Sum Query 2D - Immutable

/*
 * Given a 2D matrix matrix, find the sum of the elements inside the rectangle
 * defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
 */

/*
 * Example:
 * Given matrix = [
 *   [3, 0, 1, 4, 2],
 *   [5, 6, 3, 2, 1],
 *   [1, 2, 0, 1, 5],
 *   [4, 1, 0, 1, 7],
 *   [1, 0, 3, 0, 5]
 * ]
 * sumRegion(2, 1, 4, 3) -> 8
 * sumRegion(1, 1, 2, 2) -> 11
 * sumRegion(1, 2, 2, 4) -> 12
 */

/*
 * Note:
 * You may assume that the matrix does not change.
 * There are many calls to sumRegion function.
 * You may assume that row1 ≤ row2 and col1 ≤ col2.
 */

#include <vector>

using namespace std;

class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        if(matrix.empty())
            sums = vector<vector<int> >();
        else
        {
            int m = matrix.size();
            int n = matrix[0].size();
            sums = vector<vector<int> >(m, vector<int>(n, 0));
            sums[0][0] = matrix[0][0];
            for(int j = 1; j < n; ++j)
                sums[0][j] = sums[0][j - 1] + matrix[0][j];
            for(int i = 1; i < m; ++i)
                sums[i][0] = sums[i - 1][0] + matrix[i][0];
            for(int i = 1; i < m; ++i)
                for(int j = 1; j < n; ++j)
                    sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i][j];
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if(sums.empty())
            return -1;
        // row1 <= row2, col1 <= col2
        if(row1 == 0 && col1 == 0)
            return sums[row2][col2];
        else if(row1 == 0)
            return sums[row2][col2] - sums[row2][col1 - 1];
        else if(col1 == 1)
            return sums[row2][col2] - sums[row1 - 1][col2];
        else
            return sums[row2][col2] - sums[row2][col1 - 1]
                - sums[row1 - 1][col2] + sums[row1 - 1][col1 - 1];
    }

private:
    vector<vector<int> > sums;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
