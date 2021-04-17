// prob27: Remove Element

/*
 * Given an array nums and a value val, remove all instances of that value in-place and return the new length.
 * Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
 * The order of elements can be changed. It doesn't matter what you leave beyond the new length.
 */

/*
 * Example 1:
 * Given nums = [3,2,2,3], val = 3,
 * Your function should return length = 2, with the first two elements of nums being 2.
 * Example 2:
 * Given nums = [0,1,2,2,3,0,4,2], val = 2,
 * Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int left = 0, right = n - 1;
        while(left <= right)
        {
            if(nums[left] == val)
            {
                while(right >= 0 && nums[right] == val) right--;
                if(right == -1 || left > right) break;
                nums[left] = nums[right--];
            }
            ++left;
        }
        return left;
    }
};
