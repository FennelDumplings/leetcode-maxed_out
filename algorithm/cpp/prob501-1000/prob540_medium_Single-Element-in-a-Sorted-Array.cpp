// prob540: Single Element in a Sorted Array

/*
 * https://leetcode-cn.com/problems/single-element-in-a-sorted-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        // n 为奇数
        int N = n / 2 + 1; // 数字个数
        int left = 0, right = N - 1;
        while(left < right)
        {
            int mid = (left + right) / 2; // 第 mid 个数字
            int idx = 2 * mid; // 第 mid 个数字，正常情况下左边的那个的下标
            if(idx == n - 1)
                return nums[n - 1];
            // idx < n - 1, 有 idx + 1
            if(nums[idx] == nums[idx + 1])
                left = mid + 1;
            else
            {
                if(idx == 0)
                    return nums[0];
                else
                {
                    if(nums[idx - 1] != nums[idx])
                        return nums[idx];
                    else
                        right = mid - 1;
                }
            }
        }
        return nums[left * 2];
    }
};
