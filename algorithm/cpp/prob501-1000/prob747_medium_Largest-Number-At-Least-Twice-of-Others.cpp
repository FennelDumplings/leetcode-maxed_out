// prob747: Largest Number At Least Twice of Others

/*
 * https://leetcode-cn.com/problems/largest-number-at-least-twice-of-others/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        auto it = max_element(nums.begin(), nums.end());
        int maxx = *it;
        for(int i: nums)
        {
            if(i == maxx)
                continue;
            if(i * 2 > maxx)
                return -1;
        }
        return it - nums.begin();
    }
};
