// prob303: Range Sum Query - Immutable

/*
 * Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
 */

/*
 * Example:
 * Given nums = [-2, 0, 3, -5, 2, -1]
 * sumRange(0, 2) -> 1
 * sumRange(2, 5) -> -1
 * sumRange(0, 5) -> -3
 */

/*
 * Note:
 * You may assume that the array does not change.
 * There are many calls to sumRange function.
 */

#include <vector>

using namespace std;

class NumArray {
public:
    NumArray(vector<int>& nums) {
        if(nums.empty())
            sums = vector<int>();
        else
        {
            int n = nums.size();
            sums = vector<int>(n + 1, 0);
            for(int i = 1; i <= n; ++i)
                sums[i] = sums[i - 1] + nums[i - 1];
        }
    }

    int sumRange(int i, int j) {
        // 0 <= i <= j <= n-1
        if(sums.empty()) return 0;
        return sums[j + 1] - sums[i];
    }
private:
    vector<int> sums;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
