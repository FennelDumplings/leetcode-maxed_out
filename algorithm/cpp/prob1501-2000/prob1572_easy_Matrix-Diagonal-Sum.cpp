// prob1572: Matrix Diagonal Sum

/*
 * https://leetcode-cn.com/problems/matrix-diagonal-sum/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int ans = 0;
        int n = mat.size();
        for(int i = 0; i < n; ++i)
            ans += mat[i][i];
        for(int i = 0; i < n; ++i)
            ans += mat[n - 1 - i][i];
        if(n & 1)
            ans -= mat[n / 2][n / 2];
        return ans;
    }
};
