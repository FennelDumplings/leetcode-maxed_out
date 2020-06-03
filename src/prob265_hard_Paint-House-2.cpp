// prob265: Paint House II

/*
 * There are a row of n houses, each house can be painted with one of the k colors. The cost of
 * painting each house with a certain color is different. You have to paint all the houses such that no two
 * adjacent houses have the same color.
 * The cost of painting each house with a certain color is represented by a n x k cost matrix.
 * For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of
 * painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.
 */

/*
 * Note:
 * All costs are positive integers.
 */

/*
 * Example:
 *
 * Input: [[1,5,3],[2,9,4]]
 * Output: 5
 * Explanation: Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5;
 *              Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5.
 */

/*
 * Follow up:
 * Could you solve it in O(nk) runtime?
 */

#include <vector>
#include <climits>

using namespace std;

// O(NK^2)
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if(costs.empty()) return 0;
        int n = costs.size(), K = costs[0].size();
        vector<vector<int> > dp(n, vector<int>(K, INT_MAX));
        for(int k = 0; k < K; ++k)
            dp[0][k] = costs[0][k];
        for(int i = 1; i < n; ++i)
            for(int k = 0; k < K; ++k)
            {
                for(int prev = 0; prev < K; ++prev)
                {
                    if(prev == k) continue;
                    dp[i][k] = min(dp[i][k], dp[i - 1][prev]);
                }
                dp[i][k] += costs[i][k];
            }
        int result = dp[n - 1][0];
        for(int k = 1; k < K; ++k)
            result = min(result, dp[n - 1][k]);
        return result;
    }
};

// O(NK): 借助次小值
// 只需要记录最大值，次大值，最大值的颜色
