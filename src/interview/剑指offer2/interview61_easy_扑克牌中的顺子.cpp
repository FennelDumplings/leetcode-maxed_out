// interview61: 扑克牌中的顺子

/*
 * https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if(nums[3] == 0) return true;
        if(nums[2] == 0) return nums[4] - nums[3] <= 4 && nums[4] - nums[3] >= 1;
        if(nums[1] == 0)
        {
            int k = 2;
            for(int i = 3; i < 5; ++i)
            {
                if(nums[i] - nums[i - 1] == 2)
                {
                    if(k <= 0)
                        return false;
                    --k;
                }
                else if(nums[i] - nums[i - 1] == 3)
                {
                    if(k <= 0)
                        return false;
                    k -= 2;
                }
                else if(nums[i] - nums[i - 1] != 1)
                    return false;
            }
            return true;
        }
        if(nums[0] == 0)
        {
            int k = 1;
            for(int i = 2; i < 5; ++i)
            {
                if(nums[i] - nums[i - 1] == 2)
                {
                    if(k <= 0)
                        return false;
                    --k;
                }
                else if(nums[i] - nums[i - 1] != 1)
                    return false;
            }
            return true;
        }
        for(int i = 1; i < 5; ++i)
        {
            if(nums[i] - nums[i - 1] != 1)
                return false;
        }
        return true;
    }
};
