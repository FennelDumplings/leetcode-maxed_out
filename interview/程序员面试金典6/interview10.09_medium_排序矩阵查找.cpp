// interview10.09: 排序矩阵查找

/*
 * https://leetcode-cn.com/problems/sorted-matrix-search-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int n = matrix.size(), m = matrix[0].size();
        int i = 0, j = m - 1;
        while(i < n && j >= 0)
        {
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] > target)
                --j;
            else
                ++i;
        }
        return false;
    }
};
