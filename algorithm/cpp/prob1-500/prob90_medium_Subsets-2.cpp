// prob90: Subsets 2

/*
 * Given a collection of integers that might contain duplicates, nums,
 * return all possible subsets (the power set).
 * Note: The solution set must not contain duplicate subsets.
 */

/*
 * Example:
 *
 * Input: [1,2,2]
 * Output:
 * [
 *   [2],
 *   [1],
 *   [1,2,2],
 *   [2,2],
 *   [1,2],
 *   []
 * ]
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return  result;
        sort(nums.begin(), nums.end());
        vector<int> list;
        vector<int> visited(nums.size(), false);
        dfs(nums, 0, list, result, visited);
        return result;
    }

private:
    void dfs(vector<int> &nums, int pos, vector<int> &list,
            vector<vector<int> > &result, vector<int> &visited)
    {
        int n = nums.size();
        if(pos == n)
        {
            result.push_back(list);
            return;
        }
        if(pos > 0 && nums[pos] == nums[pos - 1] && !visited[pos - 1])
        {
            visited[pos] = false;
            dfs(nums, pos + 1, list, result, visited);
        }
        else
        {
            list.push_back(nums[pos]);
            visited[pos] = true;
            dfs(nums, pos + 1, list, result, visited);
            list.pop_back();
            visited[pos] = false;
            dfs(nums, pos + 1, list, result, visited);
        }
    }
};
