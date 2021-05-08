// prob498: Diagonal Traverse

/*
 * https://leetcode-cn.com/problems/diagonal-traverse/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        int n = matrix.size(), m = matrix[0].size();
        vector<int> result;
        for(int k = 0; k <= m + n - 1; ++k)
        {
            if(k & 1)
            {
                for(int i = max(k - m + 1, 0); i <= min(k, n - 1); ++i)
                {
                    int j = k - i;
                    result.push_back(matrix[i][j]);
                }
            }
            else
            {
                for(int i = min(k, n - 1); i >= max(k - m + 1, 0); --i)
                {
                    int j = k - i;
                    result.push_back(matrix[i][j]);
                }
            }
        }
        return result;
    }
};
