// interview17.23: 最大黑方阵

/*
 * https://leetcode-cn.com/problems/max-black-square-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findSquare(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> prefixsum_row(n, vector<int>(m + 1));
        vector<vector<int>> prefixsum_col(m, vector<int>(n + 1));
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                prefixsum_row[i][j + 1] = prefixsum_row[i][j] + matrix[i][j];
                prefixsum_col[j][i + 1] = prefixsum_col[j][i] + matrix[i][j];
            }
        }
        int x = -1, y = -1, s = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                for(int l = s + 1; l <= min(i + 1, j + 1); ++l)
                {
                    if(prefixsum_row[i][j + 1] - prefixsum_row[i][j + 1 - l] == 0 &&
                            prefixsum_row[i - l + 1][j + 1] - prefixsum_row[i - l + 1][j + 1 - l] == 0 &&
                            prefixsum_col[j][i + 1] - prefixsum_col[j][i + 1 - l] == 0 &&
                            prefixsum_col[j - l + 1][i + 1] - prefixsum_col[j - l + 1][i + 1 - l] == 0)
                    {
                        s = l;
                        x = i - l + 1;
                        y = j - l + 1;
                    }
                    if(prefixsum_row[i][j + 1] - prefixsum_row[i][j + 1 - l] != 0 ||
                            prefixsum_col[j][i + 1] - prefixsum_col[j][i + 1 - l] != 0)
                        break;
                }
            }
        if(s == 0)
            return {};
        vector<int> result{x, y, s};
        return result;
    }
};
