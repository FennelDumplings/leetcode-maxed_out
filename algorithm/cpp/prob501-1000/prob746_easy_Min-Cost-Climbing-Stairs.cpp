// prob746: Min Cost Climbing Stairs

/*
 * On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).
 * Once you pay the cost, you can either climb one or two steps.
 * You need to find minimum cost to reach the top of the floor,
 * and you can either start from the step with index 0, or the step with index 1.
 */

/*
 * Note:
 * cost will have a length in the range [2, 1000].
 * Every cost[i] will be an integer in the range [0, 999].
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];
        for(int i = 2; i < n; ++i)
            dp[i] = min(dp[i - 2], dp[i - 1]) + cost[i];
        return min(dp[n - 1], dp[n - 2]);
    }
};
