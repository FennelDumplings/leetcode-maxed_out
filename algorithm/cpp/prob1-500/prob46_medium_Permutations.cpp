// prob46: Permutations

/*
 * Given a collection of distinct integers, return all possible permutations.
 */

/*
 *Example:
 *Input: [1,2,3]
 *Output:
 *[
 *  [1,2,3],
 *  [1,3,2],
 *  [2,1,3],
 *  [2,3,1],
 *  [3,1,2],
 *  [3,2,1]
 *]
 */

#include <vector>

using namespace std;

class Solution_2 {
public:
    vector<vector<int> > permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        vector<int> cur_path;
        int n = nums.size();
        vector<bool> visited(n, false);
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
            cur_path.push_back(nums[i]);
            visited[i] = true;
            dfs(nums, pos + 1, cur_path, result, visited);
            cur_path.pop_back();
            visited[i] = false;
        }
        return;
    }
};

#include <algorithm>

// SJT
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size();
        vector<int> ori(n, 0); // 1 右，0 左
        sort(nums.begin(), nums.end());
        int minx = nums[0];
        while(true)
        {
            result.push_back(nums);
            int m = minx - 1;
            int k = -1;
            for(int i = 0; i < n; ++i)
            {
                if((i < n - 1  && ori[i] == 1 && nums[i + 1] < nums[i])
                        || (i > 0 && ori[i] == 0 && nums[i - 1] < nums[i]))
                {
                    if(nums[i] > m)
                    {
                        m = nums[i];
                        k = i;
                    }
                }
            }
            if(k == -1)
                break;
            if(ori[k] == 0)
            {
                swap(nums[k], nums[k - 1]);
                swap(ori[k], ori[k - 1]);
            }
            else
            {
                swap(nums[k], nums[k + 1]);
                swap(ori[k], ori[k + 1]);
            }
            for(int j = 0; j < n; ++j)
            {
                if(nums[j] > m)
                    ori[j] ^= 1;
            }
        }
        return result;
    }
};
