// interview57: 和为s的两个数字

/*
 * https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        if(n < 2) return {};
        int left = 0, right = n - 1;
        while(left < right)
        {
            if(nums[left] + nums[right] == target)
                return {nums[left], nums[right]};
            else if(nums[left] + nums[right] > target)
                --right;
            else
                ++left;
        }
        return {};
    }
};
