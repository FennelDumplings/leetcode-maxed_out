// prob491: Increasing Subsequences

/*
 * https://leetcode-cn.com/problems/increasing-subsequences/
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return {};
        dp = vector<vector<vector<int>>>(n);
        setting = unordered_set<int>();
        // dp[i] := [i..n-1] 且选 i 的所有递增子序列，含长度为 1
        dp[n - 1] = {{nums[n - 1]}};
        dfs(nums, 0);
        vector<vector<int>> result;
        setting.clear();
        for(int i = 0; i < n - 1; ++i)
        {
            if(setting.count(nums[i]) > 0)
                continue;
            for(const vector<int> &s: dp[i])
            {
                if((int)s.size() >= 2)
                    result.push_back(s);
            }
            setting.insert(nums[i]);
        }
        return result;
    }

private:
    vector<vector<vector<int>>> dp;
    unordered_set<int> setting;

    void dfs(const vector<int>& nums, int pos)
    {
        if(!dp[pos].empty())
            return;

        int n = nums.size();
        dp[pos] = {{nums[pos]}};
        dfs(nums, pos + 1);
        setting.clear();
        for(int i = pos + 1; i < n; ++i)
        {
            if(setting.count(nums[i]) > 0)
                continue;
            for(const vector<int> &s: dp[i])
            {
                if(nums[pos] <= s[0])
                {
                    dp[pos].push_back({nums[pos]});
                    dp[pos].back().insert(dp[pos].back().end(), s.begin(), s.end());
                }
            }
            setting.insert(nums[i]);
        }
    }
};
