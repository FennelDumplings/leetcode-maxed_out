// prob1031: Maximum Sum of Two Non-Overlapping Subarrays

/*
 * https://leetcode-cn.com/problems/maximum-sum-of-two-non-overlapping-subarrays/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
        int n = A.size();
        sums = vector<int>(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + A[i - 1];
        int ans = sliding_window(A, L, M);
        ans = max(ans, sliding_window(A, M, L));
        return ans;
    }

private:
    vector<int> sums;

    int sliding_window(const vector<int>& A, int L, int R)
    {
        // 左子数组长度 L，右子数组长度 R
        // L=2, R=3,n=7
        // 0,1,2,3,4,5,6
        // i=1,2,3=[L-1..n-R-1]
        int n = A.size();
        // dp1[i] = [0..i] 上 L 的最大，i = [L-1..n-R-1]
        vector<int> dp1(n + 1);
        dp1[L - 1] = sums[L] - sums[0];
        for(int i = L; i < n - R; ++i)
            dp1[i] = max(dp1[i - 1], sums[i + 1] - sums[i - L + 1]);
        // dp2[i] = [i..n-1] 上 R 的最大，i = [L, n-R]
        vector<int> dp2(n + 1);
        dp2[n - R] = sums[n] - sums[n - R];
        for(int i = n - R; i >= L; --i)
            dp2[i] = max(dp2[i + 1], sums[i + R] - sums[i]);

        int ans = 0;
        for(int i = L; i <= n - R; ++i)
        {
            ans = max(ans, dp1[i - 1] + dp2[i]);
        }

        return ans;
    }
};
