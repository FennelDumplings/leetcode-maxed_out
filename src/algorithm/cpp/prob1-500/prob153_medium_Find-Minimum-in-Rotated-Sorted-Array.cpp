// prob153: Find Minimum in Rotated Sorted Array

/*
 * Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 * (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 * Find the minimum element.
 * You may assume no duplicate exists in the array.
 */

/*
 * Example 1:
 * Input: [3,4,5,1,2]
 * Output: 1
 * Example 2:
 * Input: [4,5,6,7,0,1,2]
 * Output: 0
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
            else
            {
                int mid = left + (right - left) / 2;
                if(nums[mid] > nums[right])
                    left = mid + 1;
                else
                    right = mid;
            }
        }
        return nums[left];
    }
};
