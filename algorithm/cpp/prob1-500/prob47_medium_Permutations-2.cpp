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

class Solution_2 {
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


#include <algorithm>

// 字典序法
class Solution_4 {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        do{
            result.push_back(nums);
        }
        while(next_permutation(nums.begin(), nums.end()));
        return result;
    }
};

// SJT
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
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
                if(nums[j] > m || (j == 0 && nums[j] == m && ori[j] == 0) || (j == n - 1 && nums[j] == m && ori[j] == 1))
                    ori[j] ^= 1;
            }
        }
        return result;
    }
};
