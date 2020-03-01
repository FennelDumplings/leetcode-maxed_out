// prob45: Jump Game

/*
 * Given an array of non-negative integers, you are initially positioned at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Your goal is to reach the last index in the minimum number of jumps.
 */

/*
 * Example:
 * Input: [2,3,1,1,4]
 * Output: 2
 * Explanation: The minimum number of jumps to reach the last index is 2.
 *     Jump 1 step from index 0 to 1, then 3 steps to the last index.
 */

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// dp[i]:=[i..n-1]上的最小步数
// 初始化 dp[n-1]=0, 答案 dp[0]
// dp[i] = min(1+dp[i+k]) (1<=k<=nums[i])
// 朴素写法，TLE
class Solution {
public:
    int jump(vector<int>& nums) {
        // 调用方保证有解
        int n = nums.size();
        if(n == 1) return 0;
        vector<int> dp(n, INT_MAX);
        dp[n - 1] = 0;
        for(int i = n - 2; i >= 0; --i)
        {
            int k = 1;
            while(k <= nums[i] && k + i < n)
            {
                if(dp[i + k] < INT_MAX)
                    dp[i] = min(dp[i], 1 + dp[i + k]);
                ++k;
            }
        }
        return dp[0];
    }
};

// 与基本解法是同一个思路 TLE
class Solution_optim1 {
public:
    int jump(vector<int>& nums) {
        // 调用方保证有解
        int n = nums.size();
        if(n == 1) return 0;
        reverse(nums.begin(), nums.end());
        return _jump(nums, 0);
    }

private:
    int _jump(vector<int>& nums, int left)
    {
        int n = nums.size();
        if(left == n - 1) return 0;
        for(int i = n - 1; i >= left + 1; --i)
            if(nums[i] >= i - left)
                return 1 + _jump(nums, i);
        return INT_MAX;
    }
};

// DP + 剪枝
// dp[i]:=[0..i] 的最小跳数
// dp[0] = 0, 答案 dp[n - 1], 但是可以提前得到答案
// 考察 i 时，dp[i + k] 可能会更新，k=1..nums[i]
// 若 dp[i] + 1 < dp[i + k] 则 dp[i + k] = dp[i] + 1
// dp[n - 1] 被更新到，就可以返回了
class Solution_optim2 {
public:
    int jump(vector<int>& nums) {
        // 调用方保证有解
        int n = nums.size();
        if(n == 1) return 0;
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i <= n - 2; ++i)
        {
            for(int k = 1; k <= nums[i] && i + k < n; ++k)
                dp[i + k] = min(dp[i + k], dp[i] + 1);
            if(dp[n - 1] < INT_MAX)
                return dp[n - 1];
        }
        return -1;
    }
};


// 在 optim2 基础上加剪枝
// 维护一个全局的 farthest 表示当前已经更新到的最远
class Solution_optim3 {
public:
    int jump(vector<int>& nums) {
        // 调用方保证有解
        int n = nums.size();
        if(n == 1) return 0;
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        int farthest = 0;
        for(int i = 0; i <= n - 2; ++i)
        {
            for(int k = (farthest - i) + 1; k <= nums[i] && i + k < n; ++k)
            {
                dp[i + k] = min(dp[i + k], dp[i] + 1);
                farthest = i + k;
            }
            if(farthest == n - 1)
                return dp[n - 1];
        }
        return -1;
    }
};

// 贪心
// 从0开始，在第i个位置选择下一个位置时，选择能到达最远的那一个
// max(i + k + nums[i + k]) k = 1..nums[i]
// 跑的dp+比剪枝慢
class Solution_optim4 {
public:
    int jump(vector<int>& nums) {
        // 调用方保证有解
        int n = nums.size();
        if(n == 1) return 0;
        int result = 0;
        int right = 0;
        while(right < n - 1)
        {
            int next_pos = right;
            int farthest = right;
            if(right + nums[right] >= n - 1) return result + 1;
            for(int k = 1; k <= nums[right]; ++k)
            {
                if(farthest < right + k + nums[right + k])
                {
                    next_pos = right + k;
                    farthest = right + k + nums[right + k];
                }
            }
            if(next_pos == right) return -1;
            right = next_pos;
            ++result;
        }
        return result;
    }
};
