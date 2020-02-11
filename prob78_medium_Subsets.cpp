// prob78: Subsets

/*
 * Given a set of distinct integers, nums, return all possible subsets (the power set).
 */

/*
 *Example:
 *Input: nums = [1,2,3]
 *Output:
 *[
 *  [3],
 *  [1],
 *  [2],
 *  [1,2,3],
 *  [1,3],
 *  [2,3],
 *  [1,2],
 *  []
 *]
 */

#include <vector>

using namespace std;

// 排列组合是 DFS 的模板
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> list;
        dfs(nums, 0, list, result);
        return result;
    }

private:
    void dfs(vector<int> &nums, int pos, vector<int> &list, vector<vector<int> > &result)
    {
        int n = nums.size();
        if(pos == n)
        {
            result.push_back(list);
            return;
        }
        list.push_back(nums[pos]);
        dfs(nums, pos + 1, list, result);
        list.pop_back();
        dfs(nums, pos + 1, list, result);
    }
};
