// prob154: Find Minimum in Rotated Sorted Array 2

/*
 * Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 * (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 * Find the minimum element.
 * The array may contain duplicates.
 */

/*
 * Example 1:
 * Input: [1,3,5]
 * Output: 1
 * Example 2:
 * Input: [2,2,2,0,1]
 * Output: 0
 */

/*
 * Note:
 * This is a follow up problem to Find Minimum in Rotated Sorted Array.
 * Would allow duplicates affect the run-time complexity? How and why?
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.empty()) return INT_MIN;
        int n = nums.size();
        if(n == 1) return nums[0];
        int left = 0, right = n - 1;
        while(left < right)
        {
            if(nums[left] < nums[right])
                return nums[left];
            else if(nums[left] > nums[right])
            {
                int mid = left + (right - left) / 2;
                if(nums[mid] > nums[right])
                    left = mid + 1;
                else
                    right = mid;
            }
            else
            {
                while(left < right && nums[left] == nums[right])
                    --right;
            }
        }
        return nums[left];
    }
};
