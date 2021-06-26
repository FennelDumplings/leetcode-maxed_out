// prob152: Maximum Product Subarray

/*
 * Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.
 */

/*
 * Example 1:
 * Input: [2,3,-2,4]
 * Output: 6
 * Explanation: [2,3] has the largest product 6.
 * Example 2:
 * Input: [-2,0,-1]
 * Output: 0
 * Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 */

#include <vector>

using namespace std;

// 两个 dp 数组也可以滚动数组优化
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> dp_max(n, 0), dp_min(n, 0);
        dp_max[0] = nums[0];
        dp_min[0] = nums[0];
        for(int i = 1; i < n; ++i)
        {
            if(nums[i] >= 0)
            {
                dp_max[i] = max(dp_max[i - 1] * nums[i], nums[i]);
                dp_min[i] = min(dp_min[i - 1] * nums[i], nums[i]);
            }
            else
            {
                dp_max[i] = max(dp_min[i - 1] * nums[i], nums[i]);
                dp_min[i] = min(dp_max[i - 1] * nums[i], nums[i]);
            }
        }
        int result = dp_max[0];
        for(int i: dp_max) result = max(result, i);
        return result;
    }
};


class Solution_2 {
public:
    int maxProduct(vector<int>& nums) {
        int maxF = nums[0], minF = nums[0], ans = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            int mx = maxF, mn = minF;
            maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
            minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
            ans = max(maxF, ans);
        }
        return ans;
    }
};
