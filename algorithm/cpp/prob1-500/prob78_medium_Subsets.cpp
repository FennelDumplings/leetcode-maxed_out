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

// 位掩码
// 从 0 开始增加，到 1 << n 为止
class Solution_2 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > results;
        int n = nums.size();

        vector<int> result_item;
        unsigned int map = 0;
        unsigned int end = 1 << n; // 停止边界

        while(map < end)
        {
            for(int i = 0; i < n; ++i)
            {
                if((1 << i) & map)
                    result_item.push_back(nums[i]);
            }
            results.push_back(result_item);
            // 只清空元素，不释放内存
            // vector<int>().swap(MyObject)可以清空元素，释放内存。
            result_item.clear();
            ++map;
        }
        return results;
    }
};
