// prob122: Best Time to Buy and Sell Stock II

/*
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).
 * Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).
 */

/*
 * Example 1:
 * Input: [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
 *              Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
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

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        int i = 0;
        while(i < n - 1)
        {
            int j = i + 1;
            while(j < n && prices[j - 1] <= prices[j])
                ++j;
            result += prices[j - 1] - prices[i];
            i = j;
        }
        return result;
    }
};

// DP
// dp[i][j] := 考虑前i天，第i天手中有股票和无股票时手上的现金
// 初始化：dp[0][0] = 0, dp[0][1] = INT_MIN (初始手上现金为0)
// 转移 dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1])
//      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1])
class Solution_2 {
    public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<vector<int> > dp(n, vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for(int i = 1; i < n; ++i)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }
};


// 另一种写法
class Solution_3 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> dp1(n);
        vector<int> dp2(n);
        dp2[0] = -prices[0];
        for(int i = 1; i < n; ++i)
        {
            dp1[i] = max(dp1[i - 1], dp2[i - 1] + prices[i]);
            dp2[i] = max(dp2[i - 1], dp1[i - 1] - prices[i]);
        }
        return dp1[n - 1];
    }
};
