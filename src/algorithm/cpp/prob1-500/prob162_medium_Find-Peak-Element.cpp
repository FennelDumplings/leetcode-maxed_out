// prob162: Find Peak Element

/*
 * A peak element is an element that is greater than its neighbors.
 * Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element and return its index.
 * The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
 * You may imagine that nums[-1] = nums[n] = -∞.
 */

/* Example 1:
 *
 * Input: nums = [1,2,3,1]
 * Output: 2
 * Explanation: 3 is a peak element and your function should return the index number 2.
 * Example 2:
 *
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 1 or 5
 * Explanation: Your function can return either index number 1 where the peak element is 2,
 *              or index number 5 where the peak element is 6.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        if(n == 1) return 0;
        // n >= 2
        if(check_right(0, nums)) return 0;
        if(check_left(n - 1, nums)) return n - 1;
        int left = 1, right = n - 2; // n = 2 时, left = 1, right = 0
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            if(check_left(mid, nums))
            {
                if(check_right(mid, nums))
                    return mid;
                else
                    left = mid + 1;
            }
            else
                right = mid - 1;
        }
        return -1;
    }

private:
    bool check_left(int index, vector<int> &nums)
    {
        // 查 index 左边的
        // index : [1 .. n - 1]
        if(nums[index - 1] < nums[index])
            return true;
        else
            return false;
    }
    bool check_right(int index, vector<int> &nums)
    {
        // 查 index 右边的
        // index : [0 .. n - 2]
        if(nums[index] > nums[index + 1])
            return true;
        else
            return false;
    }
};
