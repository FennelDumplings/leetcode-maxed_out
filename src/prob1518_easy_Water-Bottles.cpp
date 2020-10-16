// prob1518: Water Bottles

/*
 * https://leetcode-cn.com/problems/water-bottles/
 */

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int ans = numBottles;
        while(numBottles >= numExchange)
        {
            numBottles -= numExchange;
            ++ans;
            ++numBottles;
        }
        return ans;
    }
};
