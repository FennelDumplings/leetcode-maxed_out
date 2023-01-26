// interview42: 连续子数组的最大和

/*
 * https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        int ans = dp[0];
        for(int i = 1; i < n; ++i)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
