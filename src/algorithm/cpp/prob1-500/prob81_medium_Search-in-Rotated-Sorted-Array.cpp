// prob81: Search in Rotated Sorted Array

/*
 * beforehand.
 * (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
 * You are given a target value to search. If found in the array return true, otherwise return false.
 */

/*
 * Example 1:
 * Input: nums = [2,5,6,0,0,1,2], target = 0
 * Output: true
 * Example 2:
 * Input: nums = [2,5,6,0,0,1,2], target = 3
 * Output: false
 */

/*
 * Follow up:
 * This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
 * Would this affect the run-time complexity? How and why?
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if(nums.empty()) return false;
        int n = nums.size();
        int left = 0, right = n - 1;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            if(nums[left] < nums[mid] || nums[mid] > nums[right])
            {
                if(nums[left] == target || nums[mid] == target)
                    return true;
                if(nums[left] < target && nums[mid] > target)
                {
                    right = mid - 1;
                    ++left;
                    continue;
                }
                left = mid + 1;
            }
            else if(nums[left] > nums[mid] || nums[mid] < nums[right])
            {
                if(nums[mid] == target || nums[right] == target)
                    return true;
                if(nums[mid] < target && nums[right] > target)
                {
                    left = mid + 1;
                    --right;
                    continue;
                }
                right = mid - 1;
            }
            else
            {
                if(nums[left] == target)
                    return true;
                ++left;
                --right;
            }
        }
        return false;
    }
};
