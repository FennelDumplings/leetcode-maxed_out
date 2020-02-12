// prob47: Permutations 2

/*
 * Given a collection of numbers that might contain duplicates,
 * return all possible unique permutations.
 */

/*
 *Example:
 *Input: [1,1,2]
 *Output:
 *[
 *  [1,1,2],
 *  [1,2,1],
 *  [2,1,1]
 *]
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        vector<int> cur_path;
        int n = nums.size();
        vector<bool> visited(n, false);
        sort(nums.begin(), nums.end());
        dfs(nums, 0, cur_path, result, visited);
        return result;
    }

private:
    void dfs(vector<int> &nums, int pos, vector<int> &cur_path,
            vector<vector<int> > &result, vector<bool> &visited)
    {
        // pos 是当前考虑的路径的位置
        int n = nums.size();
        if(pos == n)
        {
            result.push_back(cur_path);
            return;
        }
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            if(i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) continue;
            cur_path.push_back(nums[i]);
            visited[i] = true;
            dfs(nums, pos + 1, cur_path, result, visited);
            cur_path.pop_back();
            visited[i] = false;
        }
        return;
    }
};
