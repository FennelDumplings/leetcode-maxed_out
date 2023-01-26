// prob1252: Cells with Odd Values in a Matrix

/*
 * https://leetcode-cn.com/problems/cells-with-odd-values-in-a-matrix/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        vector<int> op_row(n);
        vector<int> op_col(m);
        for(vector<int> coord: indices)
        {
            ++op_row[coord[0]];
            ++op_col[coord[1]];
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int op_cnt = op_row[i] + op_col[j];
                if(op_cnt & 1)
                    ++ans;
            }
        return ans;
    }
};
