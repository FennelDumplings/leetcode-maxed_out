// prob485: Max Consecutive Ones

/*
 * https://leetcode-cn.com/problems/max-consecutive-one/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int left = 0;
        int ans = 0;
        while(left < n)
        {
            while(left < n && nums[left] == 0)
                ++left;
            if(left == n) break;
            int right = left + 1;
            while(right < n && nums[right] == 1)
                ++right;
            ans = max(ans, right - left);
            left = right;
        }
        return ans;
    }
};
