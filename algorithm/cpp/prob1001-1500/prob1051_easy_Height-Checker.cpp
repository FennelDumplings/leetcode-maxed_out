// prob1051: Height Checker

/*
 * https://leetcode-cn.com/problems/height-checker/
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> nums(heights.begin(), heights.end());
        sort(nums.begin(), nums.end());
        int ans = 0;
        int n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            if(heights[i] != nums[i])
                ++ans;
        }
        return ans;
    }
};
