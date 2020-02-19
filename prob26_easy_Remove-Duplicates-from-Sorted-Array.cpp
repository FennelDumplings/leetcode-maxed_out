// prob26: Remove Duplicates from Sorted Array

/*
 * Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.
 * Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
 */

/*
 * Example 1:
 * Given nums = [1,1,2],
 * Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.
 * Example 2:
 * Given nums = [0,0,1,1,1,2,2,3,3,4],
 * Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively
 */

#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 1;
        int left = 0;
        int cur = nums[left];
        for(int right = left + 1; right < n; ++right)
        {
            if(nums[right] != cur)
            {
                nums[++left] = nums[right];
                cur = nums[right];
            }
        }
        return left + 1;
    }
};
