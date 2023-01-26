// prob1314: Matrix Block Sum

/*
 * Given a m * n matrix mat and an integer K,
 * return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c]
 * for i - K <= r <= i + K, j - K <= c <= j + K, and (r, c) is a valid position in the matrix.
 */

/*
 * Example 1:
 * Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 1
 * Output: [[12,21,16],[27,45,33],[24,39,28]]
 * Example 2:
 * Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 2
 * Output: [[45,45,45],[45,45,45],[45,45,45]]
 */

/*
 * Constraints:
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n, K <= 100
 * 1 <= mat[i][j] <= 100
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > matrixBlockSum(vector<vector<int>>& mat, int K) {
        if(mat.empty()) return vector<vector<int> >();
        // init 前缀和可以本地操作
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int> > sums(m + K * 2 + 1, vector<int>(n + K * 2 + 1, 0));

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                sums[i + K + 1][j + K + 1] = mat[i][j];

        for(int i = 1; i < m + 2 * K + 1; ++i)
            for(int j = 1; j < n + 2 * K + 1; ++j)
                sums[i][j] = sums[i][j] + sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];

        vector<vector<int> > result(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                int x1, y1, x2, y2;
                x1 = 1 + i;
                y1 = 1 + j;
                x2 = 2 * K + 1 + i;
                y2 = 2 * K + 1 + j;
                result[i][j] = block_sum(sums, x1, y1, x2, y2);
            }
        }
        return result;
    }

private:
    int block_sum(vector<vector<int> > &sums, int x1, int y1, int x2, int y2)
    {
        return sums[x2][y2] - sums[x2][y1 - 1] - sums[x1 - 1][y2] + sums[x1 - 1][y1 - 1];
    }
};
