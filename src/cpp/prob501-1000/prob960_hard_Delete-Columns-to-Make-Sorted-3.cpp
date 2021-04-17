// prob960: Delete Columns to Make Sorted III

/*
 * https://leetcode-cn.com/problems/delete-columns-to-make-sorted-iii/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int m = A[0].size();
        vector<int> dp(m, 0); // dp[i]:= 考虑第 [0..i] 列, 且以 i 列结尾时候保留的列数
        // dp[i] = max(dp[j]) + 1 其中 0 <= j < i 且 第 j 列 小于第i 列(定义什么叫小于)
        dp[0] = 1;
        for(int i = 1; i < m; ++i)
        {
            for(int j = 0; j < i; ++j)
                if(less(j, i, A))
                    dp[i] = max(dp[i], dp[j]);
            ++dp[i];
        }
        int ans = 0;
        for(int i: dp)
            ans = max(ans, i);
        return m - ans;
    }

private:
    bool less(int j, int i, const vector<string>& A)
    {
        int n = A.size();
        for(int l = 0; l < n; ++l)
        {
            if(A[l][j] > A[l][i])
                return false;
        }
        return true;
    }
};
