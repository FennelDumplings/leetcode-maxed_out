// prob35: Search Insert Position

/*
 * Given a sorted array and a target value, return the index if the target is found.
 * If not, return the index where it would be if it were inserted in order.
 *
 * You may assume no duplicates in the array.
 */

/*
 * Example 1:
 * Input: [1,3,5,6], 5
 * Output: 2
 * Example 2:
 * Input: [1,3,5,6], 2
 * Output: 1
 * Example 3:
 * Input: [1,3,5,6], 7
 * Output: 4
 * Example 4:
 * Input: [1,3,5,6], 0
 * Output: 0
 */

#include<vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int left = 0, right = n;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        return right;
    }
};
