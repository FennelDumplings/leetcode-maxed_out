// prob813: Largest Sum of Averages

/*
 * We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the
 * sum of the average of each group. What is the largest score we can achieve?
 * Note that our partition must use every number in A, and that scores are not necessarily integers.
 */

/*
 * Example:
 * Input:
 * A = [9,1,2,3,9]
 * K = 3
 * Output: 20
 * Explanation:
 * The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
 * We could have also partitioned A into [9, 1], [2], [3, 9], for example.
 * That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 */

/*
 * Note:
 *
 * 1 <= A.length <= 100.
 * 1 <= A[i] <= 10000.
 * 1 <= K <= A.length.
 * Answers within 10^-6 of the correct answer will be accepted as correct.
 */

#include <vector>

using namespace std;


class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + A[i - 1];
        vector<vector<double> > dp(n, vector<double>(K + 1, 0.0));
        for(int i = 0; i < n; ++i)
            dp[i][1] = (double)(sums[n] - sums[i]) / (n - i);
        for(int k = 2; k <= K; ++k)
        {
            for(int i = n - k; i >= 0; --i)
            {
                for(int j = i + 1; j <= n - k + 1; ++j)
                {
                    dp[i][k] = max(dp[i][k], (dp[j][k - 1] + (double)(sums[j] - sums[i]) / (j - i)));
                }
            }
        }
        return dp[0][K];
    }
};
