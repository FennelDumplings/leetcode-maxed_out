// prob714: Best Time to Buy and Sell Stock with Transaction Fee

/*
 * Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i;
 * and a non-negative integer fee representing a transaction fee.
 * You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.
 * You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)
 * Return the maximum profit you can make.
 */

/*
 * Note:
 * 0 < prices.length <= 50000.
 * 0 < prices[i] < 50000.
 * 0 <= fee < 50000.
 */

/*
 * Example 1:
 * Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
 * Output: 8
 * Explanation: The maximum profit can be achieved by:
 * Buying at prices[0] = 1
 * Selling at prices[3] = 8
 * Buying at prices[4] = 4
 * Selling at prices[5] = 9
 * The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
 */

#include <vector>

using namespace std;

// DP
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> dp1(n);
        vector<int> dp2(n);
        dp2[0] = -prices[0] - fee;
        for(int i = 1; i < n; ++i)
        {
            dp1[i] = max(dp1[i - 1], dp2[i - 1] + prices[i]);
            dp2[i] = max(dp2[i - 1], dp1[i - 1] - prices[i] - fee);
        }
        return dp1[n - 1];
    }
};

// 滚动数组
class Solution_2 {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if(n <= 1) return 0;
        int prev_dp1 = 0;
        int prev_dp2 = -prices[0] - fee;
        int dp1 = 0, dp2 = 0;
        for(int i = 1; i < n; ++i)
        {
            dp1 = max(prev_dp1, prev_dp2 + prices[i]);
            dp2 = max(prev_dp2, prev_dp1 - prices[i] - fee);
            prev_dp1 = dp1;
            prev_dp2 = dp2;
        }
        return dp1;
    }
};
