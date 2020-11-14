// prob1438: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

/*
 * https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
 */

#include <vector>
#include <deque>
#include <cmath>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        deque<int> deq1, deq2;
        deq1.push_back(0);
        deq2.push_back(0);
        int ans = 1;
        int left = 0;
        for(int i = 1; i < n; ++i)
        {
            while(!deq1.empty() && abs(nums[deq1.front()] - nums[i]) > limit)
            {
                left = deq1.front() + 1;
                deq1.pop_front();
            }
            while(!deq2.empty() && abs(nums[deq2.front()] - nums[i]) > limit)
            {
                left = deq2.front() + 1;
                deq2.pop_front();
            }
            while(!deq1.empty() && nums[deq1.back()] < nums[i])
                deq1.pop_back();
            while(!deq2.empty() && nums[deq2.back()] > nums[i])
                deq2.pop_back();
            deq1.push_back(i);
            deq2.push_back(i);
            ans = max(ans, i - left + 1);
        }
        return ans;
    }
};
