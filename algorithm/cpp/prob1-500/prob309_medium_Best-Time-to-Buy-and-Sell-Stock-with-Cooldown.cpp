// prob309: Best Time to Buy and Sell Stock with Cooldown

/*
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and
 * sell one share of the stock multiple times) with the following restrictions:
 * You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
 * After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
 */

/*
 * Example:
 * Input: [1,2,3,0,2]
 * Output: 3
 * Explanation: transactions = [buy, sell, cooldown, buy, sell]
 */

#include <vector>
#include <climits>

using namespace std;

// dp1[i]:=第i天后不持有股票的最大利润
// dp2[i]:=第i天后持有股票的最大利润
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> dp1(n);
        vector<int> dp2(n);
        dp2[0] = -prices[0];
        dp1[1] = max(dp1[0], dp2[0] + prices[1]);
        dp2[1] = max(dp2[0], -prices[1]);
        for(int i = 2; i < n; ++i)
        {
            dp1[i] = max(dp1[i - 1], dp2[i - 1] + prices[i]);
            dp2[i] = max(dp2[i - 1], dp1[i - 2] - prices[i]);
        }
        return dp1[n - 1];
    }
};

// dp1[i]:=第i天后不持有，且当天不卖出的最大收益
// dp2[i]:=第i天后不持有，且当天卖出的最大收益
// dp3[i]:=第i天后持有的最大收益
class Solution_2 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> dp1(n);
        vector<int> dp2(n);
        vector<int> dp3(n);
        dp2[0] = INT_MIN / 2;
        dp3[0] = -prices[0];
        for(int i = 1; i < n; ++i)
        {
            dp1[i] = max(dp1[i - 1], dp2[i - 1]);
            dp2[i] = dp3[i - 1] + prices[i];
            dp3[i] = max(dp3[i - 1], dp1[i - 1] - prices[i]);
        }
        return max(dp1[n - 1], dp2[n - 1]);
    }
};

// Solution_2 的滚动数组优化
class Solution_3 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int prev_dp1 = 0;
        int prev_dp2 = INT_MIN / 2;
        int prev_dp3 = -prices[0];
        int dp1 = 0, dp2 = 0, dp3 = 0;
        for(int i = 1; i < n; ++i)
        {
            dp1 = max(prev_dp1, prev_dp2);
            dp2 = prev_dp3 + prices[i];
            dp3 = max(prev_dp3, prev_dp1 - prices[i]);
            prev_dp1 = dp1;
            prev_dp2 = dp2;
            prev_dp3 = dp3;
        }
        return max(dp1, dp2);
    }
};
