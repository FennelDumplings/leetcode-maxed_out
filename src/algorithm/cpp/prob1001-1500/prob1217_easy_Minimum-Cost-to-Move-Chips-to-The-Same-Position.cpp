// prob1217: Minimum Cost to Move Chips to The Same Position

/*
 * https://leetcode-cn.com/problems/minimum-cost-to-move-chips-to-the-same-position/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int cnt1 = 0, cnt0 = 0;
        for(int p: position)
        {
            if(p & 1)
                ++cnt1;
            else
                ++cnt0;
        }
        return min(cnt1, cnt0);
    }
};
