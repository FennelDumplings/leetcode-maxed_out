// prob1060: Missing Element in Sorted Array

/*
 * https://leetcode-cn.com/problems/missing-element-in-sorted-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int n = nums.size();
        return solve(nums, k, 0, n - 1);
    }

private:
    int solve(const vector<int>& nums, int k, int l, int r)
    {
        if(l == r)
            return nums[l] + k;
        int mid = (l + r + 1) / 2;
        int delta = nums[mid] - nums[l] - 1;
        // [l, mid] 的缺失数字个数 delta - (mid - l - 1)
        if(delta - (mid - l - 1) < k)
            return solve(nums, k - (delta - (mid - l - 1)), mid, r);
        else
            return solve(nums, k, l, mid - 1);
    }
};
