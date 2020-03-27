// prob188: Best Time to Buy and Sell Stock

/*
 * Say you have an array for which the i-th element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete at most k transactions.
 */

/*
 * Note:
 * You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
 */

/*
 * Example 1:
 * Input: [2,4,1], k = 2
 * Output: 2
 * Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
 * Example 2:
 * Input: [3,2,6,5,0,3], k = 2
 * Output: 7
 * Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
 *              Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 */

// 套用 porb121,123 可过的三维 dp，但这题 kk 可能很大，实测 MLE
class Solution {
public:
    int maxProfit(int kk, vector<int>& prices) {
        if(kk == 0) return 0;
        using ll = long long;
        int n = prices.size();
        if(n <= 1) return 0;
        int K = kk;
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(2, vector<int>(K + 1, 0)));
        dp[0][1][0] = -prices[0];
        for(int i = 0; i < n; ++i)
            for(int k = 1; k <= K; ++k)
                dp[i][1][k] = INT_MIN;
        for(int i = 1; i < n; ++i)
        {
            dp[i][0][0] = dp[i - 1][0][0];
            dp[i][1][0] = max((ll)dp[i - 1][1][0], (ll)dp[i - 1][0][0] - prices[i]);
            for(int k = 1; k < K; ++k)
            {
                dp[i][0][k] = max((ll)dp[i - 1][0][k], (ll)dp[i - 1][1][k - 1] + prices[i]);
                dp[i][1][k] = max((ll)dp[i - 1][1][k], (ll)dp[i - 1][0][k] - prices[i]);
            }
            dp[i][0][K] = max((ll)dp[i - 1][0][K], (ll)dp[i - 1][1][K - 1] + prices[i]);
        }
        int result = 0;
        for(int k = 1; k <= K; ++k)
            result = max(result, dp[n - 1][0][k]);
        return result;
    }
};

// dp
