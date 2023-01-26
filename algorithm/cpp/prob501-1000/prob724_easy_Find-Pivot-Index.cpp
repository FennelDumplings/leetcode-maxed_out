// prob724: Find Pivot Index

/*
 * Given an array of integers nums, write a method that returns the "pivot" index of this array.
 * We define the pivot index as the index where the sum of the numbers to the left of the index
 * is equal to the sum of the numbers to the right of the index.
 * If no such index exists, we should return -1. If there are multiple pivot indexes,
 * you should return the left-most pivot index.
 */

/*
 * Example 1:
 * Input:
 * nums = [1, 7, 3, 6, 5, 6]
 * Output: 3
 * Example 2:
 * Input:
 * nums = [1, 2, 3]
 * Output: -1
 */

#include <vector>

using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        if(n == 1) return 0;
        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];
        for(int i = 0; i < n; ++i)
        {
            int left_sum = sums[i];
            int right_sum = sums[n] - sums[i + 1];
            if(left_sum == right_sum)
                return i;
        }
        return -1;
    }
};
