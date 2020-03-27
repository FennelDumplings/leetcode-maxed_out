// prob121: Best Time to Buy and Sell Stock

/*
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
 * Note that you cannot sell a stock before you buy one.
 */

/*
 * Example 1:
 * Input: [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 * Example 2:
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 */

#include <vector>
#include <climits>

using namespace std;

// 贪心
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        int i = 0;
        while(i < n - 1)
        {
            int cur = prices[i];
            int j = i + 1;
            while(j < n && prices[j] >= cur)
            {
                if(prices[j] > cur)
                    result = max(result, prices[j] - cur);
                ++j;
            }
            i = j;
        }
        return result;
    }
};

// DP
// dp[i][j] := 考虑前i天，第i天手中有股票和无股票时手上的现金
// 初始化：dp[0][0] = 0, dp[0][1] = INT_MIN (初始手上现金为0)
// 转移 dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i])
//      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i])
class Solution_2 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<vector<int> > dp(n + 1, vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for(int i = 1; i <= n; ++i)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n][0];
    }
};
