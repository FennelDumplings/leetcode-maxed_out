// prob1230: Toss Strange Coins

/*
 * You have some coins.  The i-th coin has a probability prob[i] of facing heads when tossed.
 * Return the probability that the number of coins facing heads equals target if you toss every coin exactly once.
 */

/*
 * Example 1:
 * Input: prob = [0.4], target = 1
 * Output: 0.40000
 * Example 2:
 * Input: prob = [0.5,0.5,0.5,0.5,0.5], target = 0
 * Output: 0.03125
 */

/*
 * Constraints:
 * 1 <= prob.length <= 1000
 * 0 <= prob[i] <= 1
 * 0 <= target <= prob.length
 * Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 */

#include <vector>

using namespace std;

class Solution {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = prob.size();
        vector<vector<double> > dp(n + 1, vector<double>(n + 1, 0.0));
        dp[1][1] = prob[0];
        dp[1][0] = 1 - prob[0];
        for(int i = 2; i <= n; ++i)
        {
            dp[i][0] = dp[i - 1][0] * (1 - prob[i - 1]);
            dp[i][i] = dp[i - 1][i - 1] * prob[i - 1];
        }
        for(int i = 2; i <= n; ++i)
            for(int k = 1; k < i; ++k)
                dp[i][k] = prob[i - 1] * dp[i - 1][k - 1] + (1 - prob[i - 1]) * dp[i - 1][k];
        return dp[n][target];
    }
};
