// prob312: Burst Balloons

/*
 * Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums.
 * You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
 * Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
 * Find the maximum coins you can collect by bursting the balloons wisely.
 */

/*
 * Note:
 * You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
 * 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
 */

/*
 *Example:
 * Input: [3,1,5,8]
 * Output: 167
 * Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
 *              coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
 */

#include <vector>

using namespace std;

// 回溯
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        int ans = 0;
        dfs(nums, 0, ans);
        return ans;
    }

private:
    void dfs(vector<int> &nums, int coins, int &ans)
    {
        // coins: 当前搜索路径中可获得硬币数量
        int n = nums.size();
        if(n == 0)
        {
            // 边界
            ans = max(ans, coins);
            return;
        }
        for(int i = 0; i < n; ++i)
        {
            int tmp = nums[i];
            int delta = nums[i];
            if(i - 1 >= 0)
                delta *= nums[i - 1];
            if(i + 1 <= n - 1)
                delta *= nums[i + 1];
            nums.erase(nums.begin() + i);
            dfs(nums, coins + delta, ans);
            nums.insert(nums.begin() + i, tmp);
        }
    }
};

// 记忆化递归
class Solution_optim1 {
public:
    int maxCoins(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];

        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        dp = vector<vector<int> >(n + 2, vector<int>(n + 2, 0));
        int ans = helper(nums, 1, n);
        return ans;
    }

private:
    vector<vector<int> > dp;

    int helper(vector<int>& nums, int i, int j)
    {
        // [i..j] 上原问题的解
        // 边界
        if(i > j) return 0;
        if(dp[i][j] > 0) return dp[i][j];

        // search
        for(int k = i; k <= j; ++k)
        {
            int left = helper(nums, i, k - 1);
            int right = helper(nums, k + 1, j);
            int delta = nums[k] * nums[i - 1] * nums[j + 1];
            dp[i][j] = max(dp[i][j], left + right + delta);
        }
        return dp[i][j];
    }
};


// 自底向上 DP
class Solution_optim2 {
public:
    int maxCoins(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];

        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int> > dp = vector<vector<int> >(n + 2, vector<int>(n + 2, 0));
        for(int len = 1; len <= n; ++len)
            for(int i = 1; i <= n - len + 1; ++i)
            {
                // i <= n - len + 1
                int j = i + len - 1;
                for(int k = i; k <= j; ++k)
                    dp[i][j] = max(dp[i][j], dp[i][k - 1] + dp[k + 1][j] + nums[i - 1] * nums[j + 1] * nums[k]);
            }
        return dp[1][n];
    }
};
