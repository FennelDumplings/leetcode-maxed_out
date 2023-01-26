// prob221: Maximal Square

/*
 * Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
 */

/*
 * Example:
 * Input:
 * 1 0 1 0 0
 * 1 0 1 1 1
 * 1 1 1 1 1
 * 1 0 0 1 0
 * Output: 4
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0)); // 以 i j 为右下角的最大正方形的边长
        int result = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                if(matrix[i - 1][j - 1] == '1')
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                result = max(result, dp[i][j]);
            }
        return result * result;
    }
};
