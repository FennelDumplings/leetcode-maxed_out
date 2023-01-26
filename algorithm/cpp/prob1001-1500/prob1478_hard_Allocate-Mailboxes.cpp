// prob1478: Allocate Mailboxes

/*
 * Given the array houses and an integer k. where houses[i] is the location of the ith house along a street, your task is to allocate k mailboxes in the street.
 *
 * Return the minimum total distance between each house and its nearest mailbox.
 *
 * The answer is guaranteed to fit in a 32-bit signed integer.
 */

/*
 * Example 1:
 * Input: houses = [1,4,8,10,20], k = 3
 * Output: 5
 * Explanation: Allocate mailboxes in position 3, 9 and 20.
 * Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
 * Example 2:
 * Input: houses = [2,3,5,12,18], k = 2
 * Output: 9
 * Explanation: Allocate mailboxes in position 3 and 14.
 * Minimum total distance from each houses to nearest mailboxes is |2-3| + |3-3| + |5-3| + |12-14| + |18-14| = 9.
 * Example 3:
 * Input: houses = [7,4,6,1], k = 1
 * Output: 8
 * Example 4:
 * Input: houses = [3,6,14,10], k = 4
 * Output: 0
 */

/*
 * Constraints:
 * n == houses.length
 * 1 <= n <= 100
 * 1 <= houses[i] <= 10^4
 * 1 <= k <= n
 * Array houses contain unique integers.
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        vector<vector<int> > cost(n + 1, vector<int>(n + 1));
        vector<vector<int> > dp(k + 1, vector<int>(n + 1, INT_MAX / 2));
        sort(houses.begin(), houses.end());
        vector<int> sum(1);
        for(int i: houses)
            sum.push_back(sum.back() + i);
        for(int i = 1; i < n; ++i)
            for(int j = i + 1; j <= n; ++j)
            {
                int m = (i + j) / 2;
                cost[i][j] = houses[m - 1] * (m - i + 1) - (sum[m] - sum[i - 1]) + (sum[j] - sum[m] - houses[m - 1] * (j - m));
            }

        dp[0][0] = 0;
        for(int i = 1; i <= k; ++i)
            for(int j = 1; j <= n; ++j)
                for(int l = 0; l < j; ++l)
                    dp[i][j] = min(dp[i][j], dp[i - 1][l] + cost[l + 1][j]);

        return dp[k][n];
    }
};
