// interview16.23: 数对和

/*
 * https://leetcode-cn.com/problems/pairs-with-sum-lcci/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> pairSums(vector<int>& nums, int target) {
        if(nums.empty()) return {};
        unordered_map<int, int> mapping;
        int n = nums.size();
        vector<vector<int>> result;
        for(int i = 0; i < n; ++i)
        {
            int gap = target - nums[i];
            if(mapping.count(gap) > 0 && mapping[gap] > 0)
            {
                result.push_back({gap, nums[i]});
                --mapping[gap];
            }
            else
                ++mapping[nums[i]];
        }
        return result;
    }
};
