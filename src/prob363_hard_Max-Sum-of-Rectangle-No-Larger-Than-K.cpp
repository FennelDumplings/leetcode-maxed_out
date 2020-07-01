// prob363: Max Sum of Rectangle No Larger Than K

/*
 * Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.
 */

/*
 * Example:
 * Input: matrix = [[1,0,1],[0,-2,3]], k = 2
 * Output: 2
 * Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
 *              and 2 is the max number no larger than k (k = 2).
 */

/*
 * Note:
 * The rectangle inside the matrix must have an area > 0.
 * What if the number of rows is much larger than the number of columns?
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if(matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> sums(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m + 1, -1)));
        // dp[i][j][l] := 以 (i, j) 为右下角，宽度为 l 的最大矩形和
        int ans = INT_MIN;
        dp[0][0][1] = matrix[0][0];
        if(dp[0][0][1] <= k)
            ans = dp[0][0][1];
        // dp[0][j][1..j+1]
        for(int j = 1; j < m; ++j)
            for(int l = 1; l <= j + 1; ++l)
            {
                dp[0][j][l] = rec_sum(0, j, 0, j - l + 1, sums);
                if(dp[0][j][l] <= k)
                    ans = max(ans, dp[0][j][l]);
            }
        // dp[i][0][1]
        for(int i = 1; i < n; ++i)
        {
            dp[i][0][1] = matrix[i][0] + max(dp[i - 1][0][1], 0);
            if(dp[i][0][1] <= k)
                ans = max(ans, dp[i][0][1]);
            else
            {
                for(int ii = i - 1; ii >= 0; --ii)
                {
                    int x = rec_sum(i, 0, ii, 0, sums);
                    if(x <= k && x > ans)
                        ans = x;
                }
            }
        }
        for(int i = 1; i < n; ++i)
            for(int j = 1; j < m; ++j)
            {
                for(int l = 1; l <= j + 1; ++l)
                {
                    dp[i][j][l] = rec_sum(i, j, i, j - l + 1, sums) + max(dp[i - 1][j][l], 0);
                    if(dp[i][j][l] <= k)
                        ans = max(ans, dp[i][j][l]);
                    else
                    {
                        for(int ii = i - 1; ii >= 0; --ii)
                        {
                            int x = rec_sum(i, j, ii, j - l + 1, sums);
                            if(x <= k && x > ans)
                                ans = x;
                        }
                    }
                }
            }
        return ans;
    }

private:
    int rec_sum(int i1, int j1, int i2, int j2, const vector<vector<int>>& sums)
    {
        return sums[i1 + 1][j1 + 1] - sums[i1 + 1][j2] - sums[i2][j1 + 1] + sums[i2][j2];
    }
};
