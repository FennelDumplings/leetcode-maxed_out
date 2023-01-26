// prob198: House Robber

/*
 * You are a professional robber planning to rob houses along a street.
 * Each house has a certain amount of money stashed, the only constraint
 * stopping you from robbing each of them is that adjacent houses have security system
 * connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 *
 * Given a list of non-negative integers representing the amount of money of each house,
 * determine the maximum amount of money you can rob tonight without alerting the police.
 */

/*
 * Example 1:
 * Input: [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 * Total amount you can rob = 1 + 3 = 4.
 * Example 2:
 * Input: [2,7,9,3,1]
 * Output: 12
 * Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 */

#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);

        int mx0 = nums[0], mx1 = nums[1], mx2 = nums[0] + nums[2];
        int result = max(mx1, mx2);
        for(int i = 3; i < n; ++i)
        {
            int mx = nums[i] + max(mx0, mx1);;
            result = max(result, mx);
            mx0 = mx1;
            mx1 = mx2;
            mx2 = mx;
        }
        return result;
    }
};
