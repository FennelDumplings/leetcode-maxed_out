// prob674: Longest Continuous Increasing Subsequence

/*
 * https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 1;
        int left = 0;
        int ans = 1;
        while(left < n)
        {
            int right = left + 1;
            int prev = nums[left];
            while(right < n && prev < nums[right])
            {
                prev = nums[right];
                ++right;
            }
            ans = max(ans, right - left);
            left = right;
        }
        return ans;
    }
};
