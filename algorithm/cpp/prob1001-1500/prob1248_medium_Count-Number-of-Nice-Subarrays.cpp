// prob1248: Count Number of Nice Subarrays

/*
 * Given an array of integers nums and an integer k. A subarray is called nice if there are k odd numbers on it.
 * Return the number of nice sub-arrays.
 */

/*
 * Example 1:
 * Input: nums = [1,1,2,1,1], k = 3
 * Output: 2
 * Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
 * Example 2:
 * Input: nums = [2,4,6], k = 1
 * Output: 0
 * Explanation: There is no odd numbers in the array.
 * Example 3:
 * Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
 * Output: 16
 */

/*
 * Constraints:
 * 1 <= nums.length <= 50000
 * 1 <= nums[i] <= 10^5
 * 1 <= k <= nums.length
 */

#include <vector>

using namespace std;

class Solution {
public:
    // 前缀状态：奇数的个数
    // 当前前缀状态：cur
    // 若 cur >= k, 在历史前缀状态中查找 cur - k
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefix_state(n + 1, 0);
        prefix_state[0] = 1;
        int odd_cnt = 0;
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] & 1) ++odd_cnt;
            if(odd_cnt - k >= 0)
                result += prefix_state[odd_cnt - k];
            ++prefix_state[odd_cnt];
        }
        return result;
    }
};
