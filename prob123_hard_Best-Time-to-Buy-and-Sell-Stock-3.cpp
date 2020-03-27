// prob123: Best Time to Buy and Sell Stock III

/*
 *
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete at most two transactions.
 * Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).
 */

/*
 * Example 1:
 * Input: [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 *              Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
 * Example 2:
 * Input: [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
 *              Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
 *              engaging multiple transactions at the same time. You must sell before buying again.
 * Example 3:
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 */

#include <vector>
#include <climits>

using namespace std;

// 朴素 dp
// 边界和初始化比较麻烦, 当 K 大时候会 MLE
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        using ll = long long;
        int n = prices.size();
        if(n <= 1) return 0;
        int K = 2;
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

// 贪心
class Solution_2 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> f(n, 0);
        int lowest = prices[0];
        for(int i = 1; i < n; ++i)
        {
            f[i] = f[i - 1];
            if(prices[i] - lowest > 0)
                f[i] = max(f[i], prices[i] - lowest);
            else
                lowest = prices[i];
        }
        int result = f[n - 1];
        int highest = prices[n - 1];
        for(int i = n - 2; i >= 1; --i)
        {
            if(highest - prices[i] > 0)
                result = max(result, highest - prices[i] + f[i - 1]);
            else
                highest = prices[i];

        }
        return result;
    }
};
