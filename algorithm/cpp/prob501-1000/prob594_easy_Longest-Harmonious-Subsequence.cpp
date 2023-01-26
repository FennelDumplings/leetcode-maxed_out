// prob594: Longest Harmonious Subsequence

/*
 * https://leetcode-cn.com/problems/longest-harmonious-subsequence/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> mapping;
        for(int i = 0; i < n; ++i)
            ++mapping[nums[i]];
        int ans = 0;
        auto it = mapping.begin();
        while(it != mapping.end())
        {
            int x = it -> first;
            if(mapping.count(x + 1) > 0)
                ans = max(ans, mapping[x] + mapping[x + 1]);
            ++it;
        }
        return ans;
    }
};
