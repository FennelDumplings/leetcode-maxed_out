// interview01.08: 零矩阵

/*
 * 编写一种算法，若M × N矩阵中某个元素为0，则将其所在的行与列清零。
 */

#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<bool> row_idxs(n, false), col_idxs(m, false);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(matrix[i][j] == 0)
                {
                    row_idxs[i] = true;
                    col_idxs[j] = true;
                }
            }
        for(int i = 0; i < n; ++i)
        {
            if(row_idxs[i] == false) continue;
            for(int j = 0; j < m; ++j)
                matrix[i][j] = 0;
        }
        for(int j = 0; j < m; ++j)
        {
            if(col_idxs[j] == false) continue;
            for(int i = 0; i < n; ++i)
                matrix[i][j] = 0;
        }
    }
};
