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
// dp[i][j][k] := 考虑前i天，第i天手中有股票和无股票，且操作k次(含买和卖)时手上的现金
// 初始化：dp[0][0][0] = 0, dp[0][0][1] = INT_MIN
//         dp[0][1][0] = INT_MIN, dp[0][1][1] = INT_MIN
// 转移 dp[i][0][0] = dp[i - 1][0][0]
//      dp[i][0][1] = max(dp[i - 1][0][1], dp[i - 1][1][0] + prices[i - 1])
//      dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][0][0] - prices[i - 1])
//      dp[i][1][1] 不存在
class Solution_2 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(2, vector<int>(2, 0)));
        dp[0][1][0] = -prices[0]; // 买入
        for(int i = 1; i < n; ++i)
        {
            dp[1][0][0] = dp[1 - 1][0][0];
            dp[i][0][1] = max(dp[i - 1][0][1], dp[i - 1][1][0] + prices[i - 1]);
            dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][0][0] - prices[i - 1]);
        }
        return dp[n - 1][0][1];
    }
};

// 转换为最大子段和
class Solution_3 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> diff(n - 1);
        for(int i = 0; i < n - 1; ++i)
            diff[i] = prices[i + 1] - prices[i];
        vector<int> dp(n - 1, 0);
        dp[0] = max(0, diff[0]);
        for(int i = 1; i < n - 1; ++i)
            dp[i] = max(0, dp[i - 1] + diff[i]);
        int result = 0;
        for(int a: dp) result = max(result, a);
        return result;
    }
};

// 转换为最大子段和
// diff 数组和 dp 数组均可优化掉
class Solution_4 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int last = 0;
        int result = 0;
        for(int i = 0; i < n - 1; ++i)
        {
            last = max(0, last + prices[i + 1] - prices[i]);
            result = max(result, last);
        }
        return result;
    }
};
