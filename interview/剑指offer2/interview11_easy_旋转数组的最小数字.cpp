// interview11: 旋转数组的最小数字

/*
 * https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minArray(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        if(n == 1) return nums[0];
        int left = 0, right = n - 1;
        while(left < right)
        {
            if(nums[left] < nums[right])
                return nums[left];
            int mid = (left + right) / 2;
            if(nums[left] > nums[right])
            {
                if(nums[mid] >= nums[left])
                    left = mid + 1;
                else // nums[mid] <= nums[right]
                    right = mid;
            }
            else // nums[left] == nums[right]
            {
                if(nums[mid] > nums[left])
                    left = mid + 1;
                else if(nums[mid] < nums[left])
                    right = mid;
                else
                {
                    ++left;
                    --right;
                }
            }
        }
        return nums[left];
    }
};
