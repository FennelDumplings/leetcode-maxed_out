// prob1362: Greatest Sum Divisible by Three

/*
 * https://leetcode-cn.com/problems/greatest-sum-divisible-by-three/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution_3 {
public:
    int maxSumDivThree(vector<int>& nums) {
        const int MAXX = 4e4 + 1;
        if(nums.empty()) return 0;
        int min1 = MAXX, sub_min1 = MAXX, min2 = MAXX, sub_min2 = MAXX;
        int sum = 0;
        for(int num: nums)
        {
            sum += num;
            if(num % 3 == 1)
            {
                if(num < min1)
                {
                    sub_min1 = min1;
                    min1 = num;
                }
                else if(num < sub_min1)
                    sub_min1 = num;
            }
            else if(num % 3 == 2)
            {
                if(num < min2)
                {
                    sub_min2 = min2;
                    min2 = num;
                }
                else if(num < sub_min2)
                    sub_min2 = num;
            }
        }
        int ans = sum;
        if(sum % 3 == 1)
        {
            if(min1 < MAXX)
                ans = sum - min1;
            if(sub_min2 < MAXX)
                ans = max(ans, sum - min2 - sub_min2);
        }
        if(sum % 3 == 2)
        {
            if(min2 < MAXX)
                ans = sum - min2;
            if(sub_min1 < MAXX)
                ans = max(ans, sum - min1 - sub_min1);
        }
        return ans;
    }
};

/*
dp[i][j] : [0, i]区间选择能被3余j的和的最大值
nums[i] % 3 == 0:
    dp[i][0] = max(dp[i-1][0], dp[i-1][0] + nums[i]);
    dp[i][1] = max(dp[i-1][1], dp[i-1][1] + nums[i]);
    dp[i][2] = max(dp[i-1][2], dp[i-1][2] + nums[i]);

nums[i] % 3 == 1:
    dp[i][0] = max(dp[i-1][0], dp[i-1][2] + nums[i])
    dp[i][1] = max(dp[i-1][1], dp[i-1][0] + nums[i])
    dp[i][2] = max(dp[i-1][2], dp[i-1][1] + nums[i]);


nums[i] % 3 == 2:
    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + nums[i])
    dp[i][1] = max(dp[i-1][1], dp[i-1][2] + nums[i])
    dp[i][2] = max(dp[i-1][2], dp[i-1][0] + nums[i])

dp[i][j] = max(dp[i - 1][j],
                dp[i - 1][(j - nums[i] % 3 + 3) % 3] + nums[i])
*/

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));
        dp[0][0] = 0; dp[0][1] = dp[0][2] = INT_MIN;
        for (int i = 1; i <= n; i++) {
            int x = nums[i - 1];
            for(int j = 0; j < 3; ++j)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][(j - (x % 3) + 3) % 3]);
        }
        return dp[n][0];
    }
};



class Solution_2 {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));
        dp[0][0] = 0; dp[0][1] = dp[0][2] = INT_MIN;
        for (int i = 1; i <= n; i++) {
            int x = nums[i - 1];
            if (x % 3 == 0) {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][0] + x);
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][1] + x);
                dp[i][2] = max(dp[i - 1][2], dp[i - 1][2] + x);
            } else if (x % 3 == 1) {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] + x);
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + x);
                dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + x);
            } else {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + x);
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][2] + x);
                dp[i][2] = max(dp[i - 1][2], dp[i - 1][0] + x);
            }
        }
        return dp[n][0];
    }
};

