// prob256: Paint House

/*
 * There are a row of n houses, each house can be painted with one of the three
 * colors: red, blue or green. The cost of painting each house with a certain color is different.
 * You have to paint all the houses such that no two adjacent houses have the same color.
 * The cost of painting each house with a certain color is represented by a n x 3 cost matrix.
 * For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the
 * cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.
 */

/*
 * Example:
 *
 * Input: [[17,2,17],[16,16,5],[14,3,19]]
 * Output: 10
 * Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue.
 *              Minimum cost: 2 + 5 + 3 = 10.
 */

/*
 * Note:
 * All costs are positive integers.
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.empty()) return 0;
        const int N = 3;
        int state[N][N - 1] = {{1, 2}, {0, 2}, {0, 1}};
        int n = costs.size();
        vector<vector<int> > dp(n, vector<int>(3, INT_MAX));
        for(int color = 0; color < N; ++color)
            dp[0][color] = costs[0][color];
        for(int i = 1; i < n; ++i)
        {
            for(int color = 0; color < N; ++color)
            {
                for(int k = 0; k < N - 1; ++k)
                    dp[i][color] = min(dp[i][color], dp[i - 1][state[color][k]]);
                dp[i][color] += costs[i][color];
            }
        }
        int result = dp[n - 1][0];
        for(int color = 1; color < N; ++color)
            result = min(result, dp[n - 1][color]);
        return result;
    }
};
