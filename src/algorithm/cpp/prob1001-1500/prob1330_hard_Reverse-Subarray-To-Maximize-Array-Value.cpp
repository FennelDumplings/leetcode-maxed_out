// prob1330: Reverse Subarray To Maximize Array Value

/*
 * https://leetcode-cn.com/problems/reverse-subarray-to-maximize-array-value/
 */

#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        // ans 为翻转 (0, n-1) 的结果
        for(int i = 0; i < n - 1; ++i)
            ans += abs(nums[i] - nums[i + 1]);
        int S0 = ans;

        // 翻转 (0, j)
        for(int j = 0; j < n - 1; ++j)
            ans = max(ans, S0 - abs(nums[j] - nums[j + 1]) + abs(nums[0] - nums[j + 1]));

        // 翻转 (i, n-1)
        for(int i = 1; i < n; ++i)
            ans = max(ans, S0 - abs(nums[i] - nums[i - 1]) + abs(nums[n - 1] - nums[i - 1]));

        // 翻转 (i, j)
        for(int d1: {-1, 1})
            for(int d2: {-1, 1})
            {
                int max_F = INT_MIN;
                int S = INT_MIN;
                for(int j = 1; j < n - 1; ++j)
                {
                    int gj = -d1 * nums[j] - d2 * nums[j + 1] - abs(nums[j] - nums[j + 1]);
                    max_F = max(max_F, d1 * nums[j - 1] + d2 * nums[j] - abs(nums[j - 1] - nums[j]));
                    S = max(S, gj + max_F);
                    ans = max(ans, S0 + S);
                }
            }

        return ans;
    }
};
