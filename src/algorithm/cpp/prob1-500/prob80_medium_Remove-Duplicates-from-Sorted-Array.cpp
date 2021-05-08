// prob80: Remove Duplicates from Sorted Array

/*
 * Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most twice and return the new length.
 * Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
 */

/*
 * Example 1:
 * Given nums = [1,1,1,2,2,3],
 * Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
 * It doesn't matter what you leave beyond the returned length.
 * Example 2:
 * Given nums = [0,0,1,1,1,1,2,3,3],
 * Your function should return length = 7, with the first seven elements of nums being modified to 0, 0, 1, 1, 2, 3 and 3 respectively.
 * It doesn't matter what values are set beyond the returned length.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n <= 2) return n;
        // n >= 3;
        int iter = 2;
        while(iter < n && (nums[iter - 2] != nums[iter - 1] || nums[iter - 1] != nums[iter])) ++iter;
        if(iter == n) return iter;
        int left = iter + 1;
        while(left < n && nums[left] == nums[iter - 1]) ++left;
        if(left == n) return iter;
        while(left < n)
        {
            if(left + 1 == n || nums[left] != nums[left + 1])
            {
                nums[iter] = nums[left];
                ++iter;
                ++left;
            }
            else
            {
                nums[iter] = nums[left];
                nums[iter + 1] = nums[left + 1];
                iter += 2;
                left += 2;
            }
            while(left < n && nums[left] == nums[iter - 1]) ++left;
        }
        return iter;
    }
};
