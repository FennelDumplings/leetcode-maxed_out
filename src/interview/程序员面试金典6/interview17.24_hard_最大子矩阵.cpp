// interview17.24: 最大子矩阵

/*
 * 给定一个正整数和负整数组成的 N × M 矩阵，编写代码找出元素总和最大的子矩阵。
 * 返回一个数组 [r1, c1, r2, c2]，其中 r1, c1 分别代表子矩阵左上角的行号和列号，r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。
 */

/*
 * 输入:
 * [
 *    [-1,0],
 *    [0,-1]
 * ]
 */

/*
 * 说明：
 * 1 <= matrix.length, matrix[0].length <= 200
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> sums(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m + 1, -1)));
        // dp[i][j][l] := 以 (i, j) 为右下角，宽度为 l 的最大矩形和
        vector<vector<vector<int>>> dp2(n, vector<vector<int>>(m, vector<int>(m + 1, 0)));
        // dp2[i][j][l] := 以 (i, j) 为右下角，宽度为 l 的最大矩形和对应的上界下标
        dp[0][0][1] = matrix[0][0];
        for(int j = 1; j < m; ++j)
            for(int l = 1; l <= j + 1; ++l)
                dp[0][j][l] = rec_sum(0, j, 0, j - l + 1, sums);
        for(int i = 1; i < n; ++i)
        {
            dp[i][0][1] = matrix[i][0] + max(dp[i - 1][0][1], 0);
            if(dp[i - 1][0][1] > 0)
                dp2[i][0][1] = dp2[i - 1][0][1];
            else
                dp2[i][0][1] = i;
        }
        for(int i = 1; i < n; ++i)
            for(int j = 1; j < m; ++j)
            {
                for(int l = 1; l <= j + 1; ++l)
                {
                    dp[i][j][l] = rec_sum(i, j, i, j - l + 1, sums) + max(dp[i - 1][j][l], 0);
                    if(dp[i - 1][j][l] > 0)
                        dp2[i][j][l] = dp2[i - 1][j][l];
                    else
                        dp2[i][j][l] = i;
                }
            }
        int max_sum = INT_MIN;
        int mi = -1, mj = -1, ml = -1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                for(int l = 1; l <= j + 1; ++l)
                    if(dp[i][j][l] > max_sum)
                    {
                        max_sum = dp[i][j][l];
                        mi = i;
                        mj = j;
                        ml = l;
                    }
        return vector<int>{dp2[mi][mj][ml], mj - ml + 1, mi, mj};
    }

private:
    int rec_sum(int i1, int j1, int i2, int j2, const vector<vector<int>>& sums)
    {
        return sums[i1 + 1][j1 + 1] - sums[i1 + 1][j2] - sums[i2][j1 + 1] + sums[i2][j2];
    }
};
