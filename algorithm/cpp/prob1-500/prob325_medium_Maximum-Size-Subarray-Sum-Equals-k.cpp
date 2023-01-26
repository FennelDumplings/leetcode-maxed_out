// prob325: Maximum Size Subarray Sum Equals k

/*
 * Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.
 */

/*
 * Note:
 * The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.
 */

/*
 * Example 1:
 * Input: nums = [1, -1, 5, -2, 3], k = 3
 * Output: 4
 * Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
 * Example 2:
 * Input: nums = [-2, -1, 2, 1], k = 1
 * Output: 2
 * Explanation: The subarray [-1, 2] sums to 1 and is the longest.
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<int> sums(n + 1, 0);
        unordered_map<int, int> mapping;
        mapping.insert(pair<int, int>(0, 0)); // 前缀和的值 -> 对应前缀和数组的最左索引

        int result = 0;
        // nums[i..j] 的和 sums[j] - sums[i - 1]
        for(int i = 1; i <= n; ++i)
        {
            sums[i] = sums[i - 1] + nums[i - 1];
            int gap = sums[i] - k;
            if(mapping.find(gap) != mapping.end())
                result = max(result, i - mapping[gap]);
            if(mapping.find(sums[i]) == mapping.end())
                mapping.insert(pair<int, int>(sums[i], i));
        }
        return result;
    }
};
