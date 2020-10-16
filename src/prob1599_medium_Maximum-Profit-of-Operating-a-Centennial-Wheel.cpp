// prob1599: Maximum Profit of Operating a Centennial Wheel

/*
 * https://leetcode-cn.com/problems/maximum-profit-of-operating-a-centennial-wheel/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int tourist = 0;
        int profit = 0;
        int revenue = 0, cost = 0;
        int n = customers.size();
        int ans = -1;
        for(int i = 0; i < n || tourist > 0; ++i)
        {
            if(i < n)
                tourist += customers[i];
            int board = min(4, tourist);
            tourist -= board;
            revenue += board * boardingCost;
            cost += runningCost;
            if(revenue - cost > profit)
            {
                profit = revenue - cost;
                ans = i;
            }
        }
        if(ans != -1)
            ++ans;
        return ans;
    }
};
