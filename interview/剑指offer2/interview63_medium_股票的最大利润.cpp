// interview63: 股票的最大利润

/*
 * https://leetcode-cn.com/problems/gu-piao-de-zui-da-li-run-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int minx = prices[0];
        int ans = 0;
        for(int i = 1; i < n; ++i)
        {
            if(prices[i] > minx)
                ans = max(ans, prices[i] - minx);
            else if(prices[i] < minx)
                minx = prices[i];
        }
        return ans;
    }
};
