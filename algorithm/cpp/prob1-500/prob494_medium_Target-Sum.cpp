// prob494: Target Sum

/*
 * You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -.
 * For each integer, you should choose one from + and - as its new symbol.
 * Find out how many ways to assign symbols to make sum of integers equal to target S.
 */

/*
 * Note:
 * The length of the given array is positive and will not exceed 20.
 * The sum of elements in the given array will not exceed 1000.
 * Your output answer is guaranteed to be fitted in a 32-bit integer.
 */

/*
 * Example 1:
 * Input: nums is [1, 1, 1, 1, 1], S is 3.
 * Output: 5
 * Explanation:
 * -1+1+1+1+1 = 3
 *  +1-1+1+1+1 = 3
 *  +1+1-1+1+1 = 3
 *  +1+1+1-1+1 = 3
 *  +1+1+1+1-1 = 3
 *  There are 5 ways to assign symbols to make the sum of nums be target 3.
 */

#include <vector>
#include <climits>
#include <numeric>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);

        if (!(-sum <= S && S <= sum))
            return 0;

        vector<vector<int>> dp(n + 1, vector<int>(2 * sum + 1, 0));
        dp[0][0 + sum] = 1;

        for(int i = 1; i <= n; i++)
            for (int j = -sum; j <= sum; j++)
            {
                if(-sum <= j - nums[i - 1])
                    dp[i][j + sum] += dp[i - 1][j - nums[i - 1] + sum];
                if(j + nums[i - 1] <= sum)
                    dp[i][j + sum] += dp[i - 1][j + nums[i - 1] + sum];
            }

        return dp[n][S + sum];

    }
};
