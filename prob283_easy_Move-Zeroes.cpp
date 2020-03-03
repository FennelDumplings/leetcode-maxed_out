// prob283: Move Zeroes

/*
 * Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
 */

/*
 * Example:
 * Input: [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 */

/*
 * Note:
 * You must do this in-place without making a copy of the array.
 * Minimize the total number of operations.
 */

#include <vector>

using namespace  std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        int left = 0, right = 0;
        while(left < n && right < n)
        {
            while(left < n && nums[left] != 0) ++left;
            if(left < n)
            {
                right = left + 1;
                while(right < n && nums[right] == 0) ++right;
                if(right < n)
                {
                    _swap(nums, left, right);
                    ++left;
                    ++right;
                }
            }
        }
    }

private:
    void _swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};

// 另一写法
class Solution_2 {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        for (int lastNonZeroFoundAt = 0, cur = 0; cur < n; cur++) {
            if (nums[cur] != 0) {
                swap(nums[lastNonZeroFoundAt++], nums[cur]);
            }
        }
    }
};
