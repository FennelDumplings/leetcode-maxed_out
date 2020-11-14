// prob1292: Maximum Side Length of a Square with Sum Less than or Equal to Threshold

/*
 * https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size(), m = mat[0].size();
        sums.assign(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                sums[i][j] = mat[i - 1][j - 1] + sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1];
            }
        int right = min(n, m);
        int left = 0;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            int res = check(mid);
            if(res > threshold)
                right = mid - 1;
            else
                left = mid;
        }
        return left;
    }

private:
    vector<vector<int>> sums;

    int get_sum(int i1, int j1, int i2, int j2)
    {
        return sums[i2 + 1][j2 + 1] - sums[i2 + 1][j1] - sums[i1][j2 + 1] + sums[i1][j1];
    }

    int check(int mid)
    {
        int n = sums.size() - 1, m = sums[0].size() - 1;
        int ans = sums[n][m];
        for(int i = mid - 1; i < n; ++i)
            for(int j = mid - 1; j < m;  ++j)
                ans = min(ans, get_sum(i - mid + 1, j - mid + 1, i, j));
        return ans;
    }
};
