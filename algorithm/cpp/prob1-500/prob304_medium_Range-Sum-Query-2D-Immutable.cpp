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
            sums = vector<vector<int> >(m + 1, vector<int>(n + 1, 0));
            for(int i = 1; i <= m; ++i)
                for(int j = 1; j <= n; ++j)
                    sums[i][j] = sums[i][j - 1] + sums[i - 1][j]
                        - sums[i - 1][j - 1] + matrix[i - 1][j - 1];
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if(sums.empty()) return -1;
        // row1 <= row2, col1 <= col2
        return sums[row2 + 1][col2 + 1] - sums[row2 + 1][col1]
            - sums[row1][col2 + 1] + sums[row1][col1];
    }

private:
    vector<vector<int> > sums;
};
