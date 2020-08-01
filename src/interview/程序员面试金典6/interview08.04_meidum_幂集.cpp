// interview04.08: 幂集

/*
 * https://leetcode-cn.com/problems/power-set-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> item;
        dfs(nums, 0, item, result);
        return result;
    }

private:
    void dfs(const vector<int>& nums, int pos, vector<int>& item, vector<vector<int>>& result)
    {
        int n = nums.size();
        if(pos == n)
        {
            result.push_back(item);
            return;
        }

        dfs(nums, pos + 1, item, result);

        item.push_back(nums[pos]);
        dfs(nums, pos + 1, item, result);
        item.pop_back();
    }
};
