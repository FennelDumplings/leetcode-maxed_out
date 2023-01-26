// prob55: Jump Game

/*
 * Given an array of non-negative integers, you are initially positioned at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Determine if you are able to reach the last index.
 */

/*
 * Example 1:
 * Input: [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 * Example 2:
 * Input: [3,2,1,0,4]
 * Output: false
 * Explanation: You will always arrive at index 3 no matter what. Its maximum
 *              jump length is 0, which makes it impossible to reach the last index.
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.empty()) return false;
        int n = nums.size();
        if(n == 1) return true;
        vector<bool> dp(n, false);
        dp[0] = true;
        int right_true = 0;
        for(int i = 0; i <= n - 2; ++i)
        {
            int jump_to = nums[i] + i;
            if(dp[i] && jump_to >= n - 1)
                return true;
            if(dp[i] && jump_to >= right_true)
            {
                for(int j = right_true + 1; j <= jump_to; ++j)
                    dp[j] = true;
                right_true = jump_to;
            }
        }
        return false;
    }
};

