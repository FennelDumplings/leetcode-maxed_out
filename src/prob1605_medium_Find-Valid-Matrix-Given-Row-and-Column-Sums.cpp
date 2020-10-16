// prob1605: Find Valid Matrix Given Row and Column Sums

/*
 * https://leetcode-cn.com/problems/find-valid-matrix-given-row-and-column-sums/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int n = rowSum.size(), m = colSum.size();
        vector<vector<int>> result(n, vector<int>(m, 0));
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                int x = rowSum[i];
                int y = colSum[j];
                int z = min(x, y);
                result[i][j] = z;
                rowSum[i] -= z;
                colSum[j] -= z;
            }
        }
        return result;
    }
};
