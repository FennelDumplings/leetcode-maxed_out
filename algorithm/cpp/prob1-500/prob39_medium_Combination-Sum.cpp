// prob39: Combination Sum

/*
 * Given a set of candidate numbers (candidates) (without duplicates) and a target number (target),
 * find all unique combinations in candidates where the candidate numbers sums to target.
 * The same repeated number may be chosen from candidates unlimited number of times.
 * Note:
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 */

/*
 * Example 1:
 * Input: candidates = [2,3,6,7], target = 7,
 * A solution set is:
 * [
 *   [7],
 *   [2,2,3]
 * ]
 * Example 2:
 * Input: candidates = [2,3,5], target = 8,
 * A solution set is:
 * [
 *   [2,2,2,2],
 *   [2,3,3],
 *   [3,5]
 * ]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if(candidates.empty()) return vector<vector<int> >();
        int n = candidates.size();
        vector<vector<int> > result;
        vector<int> cur_path;
        int cur_sum = 0;
        int pos = 0; // 当前考虑的是不使用 pos 位置之前元素的解
        dfs(candidates, result, pos, cur_sum, cur_path, target, n);
        return result;
    }

private:
    void dfs(vector<int>& candidates, vector<vector<int> >& result, int pos, int cur_sum, vector<int>& cur_path, int target, int n)
    {
        if(cur_sum > target)
            return;
        else if(cur_sum == target)
        {
            result.push_back(cur_path);
            return;
        }

        for(int i = pos; i < n; ++i)
        {
            int cur_num = candidates[i];
            cur_path.push_back(cur_num);
            cur_sum += cur_num;
            dfs(candidates, result, i, cur_sum, cur_path, target, n);
            cur_sum -= cur_num;
            cur_path.pop_back();
        }
    }
};
