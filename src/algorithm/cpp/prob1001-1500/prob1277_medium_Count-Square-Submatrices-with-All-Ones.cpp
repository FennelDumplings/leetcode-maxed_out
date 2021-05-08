// prob1277: Count Square Submatrices with All Ones

/*
 * https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/
 */

#include <vector>

using namespace std;

// dp[i][j] := 以 (i, j) 为右下角的最大正方形的边长
// li[i][j] := 从 (i, j) 向上的最长连续 1 个数
// lj[i][j] := 从 (i, j) 向左的最长连续 1 个数

class Solution {
public:
    int countSquares(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        vector<vector<int>> dp(n, vector<int>(m));
        vector<vector<int>> li(n, vector<int>(m));
        vector<vector<int>> lj(n, vector<int>(m));
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(A[i][j] == 0) continue;
                dp[i][j] = 1;
                li[i][j] = 1;
                lj[i][j] = 1;
                if(i > 0)
                    li[i][j] += li[i - 1][j];
                if(j > 0)
                    lj[i][j] += lj[i][j - 1];
                if(i > 0 && j > 0)
                    dp[i][j] = min(1 + dp[i - 1][j - 1], min(li[i][j], lj[i][j]));
                ans += dp[i][j];
            }
        return ans;
    }
};
