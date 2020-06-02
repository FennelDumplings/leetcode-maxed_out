// prob377: Combination Sum IV

/*
 * Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.
 */

/*
 * Example:
 * nums = [1, 2, 3]
 * target = 4
 * The possible combination ways are:
 * (1, 1, 1, 1)
 * (1, 1, 2)
 * (1, 2, 1)
 * (1, 3)
 * (2, 1, 1)
 * (2, 2)
 * (3, 1)
 * Note that different sequences are counted as different combinations.
 * Therefore the output is 7.
 */

/*
 * Follow up:
 * What if negative numbers are allowed in the given array?
 * How does it change the problem?
 * What limitation we need to add to the question to allow negative numbers?
 */

#include <vector>
#include <algorithm>

using namespace std;

// 背包问题

// Follow up
// 对于进阶问题的思考
// 1、如果给定的数组中含有负数会怎么样？问题会产生什么变化？
//
// 如果有负数，相当于给定数组中的元素有了更多的组合，特别是出现了一对相反数的时候，例如题目中的示例 [-4, 1, 2, 3, 4]，target = 4 的时候，-4 和 4 可以无限次地、成对添加到题目中的示例中，成为新的组合，那么这道问题就没有什么意义了。
//
// 仔细思考，负数我只要不选它就行了。但由于这道问题的问法是“组合”，因此我们要保证有负数参与进来，不能够与已有的正数的组合之和为 0 即可。
//
// 2、我们需要在题目中添加什么限制来允许负数的出现？
//
// 如果有负数参与进来，不能够与已有的正数的组合之和为 0 ；
// 或者限制负数的使用次数，设计成类似 0-1 背包问题的样子。

// 排序+剪枝
// 记忆化
// dp[i] = sum{dp[i - num] for num in nums and if i >= num}
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<int> dp(target + 1, -1);
        dp[0] = 0;
        dfs(nums, target, dp);
        return dp[target];
    }

private:
    int dfs(const vector<int>& nums, int target, vector<int>& dp)
    {
        if(dp[target] != -1)
            return dp[target];

        dp[target] = 0;
        for(int num: nums)
        {
            if(num > target)
                break;
            else if(num == target)
                ++dp[target];
            else
                dp[target] += dfs(nums, target - num, dp);
        }
        return dp[target];
    }
};

// 排序 + 剪枝
class Solution_2 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int result = 0;
        sort(nums.begin(), nums.end());
        dfs(nums, target, result);
        return result;
    }

private:
    void dfs(const vector<int>& nums, int target, int& result)
    {
        if(target < 0)
            return;
        if(target == 0)
        {
            ++result;
            return;
        }
        for(int num: nums)
        {
            if(num > target)
                break;
            dfs(nums, target - num, result);
        }
    }
};

// DFS
// TLE
class Solution_2 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int result = 0;
        dfs(nums, target, result);
        return result;
    }

private:
    void dfs(const vector<int>& nums, int target, int& result)
    {
        if(target < 0)
            return;
        if(target == 0)
        {
            ++result;
            return;
        }
        for(int num: nums)
            dfs(nums, target - num, result);
    }
};
