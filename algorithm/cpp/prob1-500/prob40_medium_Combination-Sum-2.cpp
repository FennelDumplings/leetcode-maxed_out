// prob40: Combination Sum II

/*
 * Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.
 *
 * Each number in candidates may only be used once in the combination.
 *
 * Note:
 *
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 */

/*
 * Example 1:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8,
 * A solution set is:
 * [
 *   [1, 7],
 *   [1, 2, 5],
 *   [2, 6],
 *   [1, 1, 6]
 * ]
 * Example 2:
 * Input: candidates = [2,5,2,1,2], target = 5,
 * A solution set is:
 * [
 *   [1,2,2],
 *   [5]
 * ]
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        if(candidates.empty()) return vector<vector<int> >();
        int n = candidates.size();
        sort(candidates.begin(), candidates.end());
        vector<vector<int> > result;
        vector<int> cur_path;
        int cur_sum = 0;
        int pos = 0;
        dfs(candidates, result, pos, cur_sum, cur_path, target, n);
        return result;
    }

private:
    void dfs(vector<int>& candidates, vector<vector<int> >& result, int pos, int cur_sum, vector<int>& cur_path, int target, int n)
    {
        if(cur_sum == target)
        {
            result.push_back(cur_path);
            return;
        }
        else if(cur_sum > target)
            return;

        for(int i = pos; i < n; ++i)
        {
            int cur_num = candidates[i];
            // 共两次循环，一次原生for循环，一次递归
            if(i > pos && candidates[i - 1] == candidates[i])
                continue;
            cur_sum += cur_num;
            cur_path.push_back(cur_num);
            dfs(candidates, result, i + 1, cur_sum, cur_path, target, n);
            cur_sum -= cur_num;
            cur_path.pop_back();
        }
    }
};
