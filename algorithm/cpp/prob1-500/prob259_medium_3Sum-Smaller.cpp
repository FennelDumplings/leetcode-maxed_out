// prob259: 3Sum Smaller

/*
 * Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
 */

/*
 * Example:
 *
 * Input: nums = [-2,0,1,3], and target = 2
 * Output: 2
 * Explanation: Because there are two triplets which sums are less than 2:
 *              [-2,0,1]
 *              [-2,0,3]
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n < 3) return 0;
        sort(nums.begin(), nums.end());
        int result = 0;
        for(int i = 0; i <= n - 3; ++i)
        {
            int gap = target - nums[i];
            int left = i + 1, right = n - 1;
            while(left < right)
            {
                if(nums[left] + nums[right] >= gap)
                    --right;
                else
                {
                    result += (right - left);
                    ++left;
                }
            }
        }
        return result;
    }
};
