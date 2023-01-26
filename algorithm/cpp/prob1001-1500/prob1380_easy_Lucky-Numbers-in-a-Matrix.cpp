// prob1380: Lucky Numbers in a Matrix

/*
 * Given a m * n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
 * A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
 */

/*
 * Example 1:
 * Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
 * Output: [15]
 * Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column
 * Example 2:
 * Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
 * Output: [12]
 * Explanation: 12 is the only lucky number since it is the minimum in its row and the maximum in its column.
 * Example 3:
 * Input: matrix = [[7,8],[1,2]]
 * Output: [7]
 */

/*
 * Constraints:
 * m == mat.length
 * n == mat[i].length
 * 1 <= n, m <= 50
 * 1 <= matrix[i][j] <= 10^5.
 * All elements in the matrix are distinct.
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<int> row_min_idx(n, -1);
        vector<int> col_max_idx(m, -1);
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                if(row_min_idx[i] < 0 || matrix[i][row_min_idx[i]] > matrix[i][j])
                    row_min_idx[i] = j;
                if(col_max_idx[j] < 0 || matrix[col_max_idx[j]][j] < matrix[i][j])
                    col_max_idx[j] = i;
            }
        }
        vector<int> result;
        for(int i = 0; i < n; ++i)
        {
            if(col_max_idx[row_min_idx[i]] == i)
                result.push_back(matrix[i][row_min_idx[i]]);
        }
        return result;
    }
};
