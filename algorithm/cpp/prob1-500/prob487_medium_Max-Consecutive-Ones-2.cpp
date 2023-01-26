// prob487: Max Consecutive Ones II

/*
 * https://leetcode-cn.com/problems/max-consecutive-ones-ii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int left = 0;
        int prev_len = 0;
        bool prev1 = false; // 前驱刚好以一个0
        int ans = 1;
        while(left < n)
        {
            int iter = left;
            while(iter < n && nums[iter] == 0)
                ++iter;
            if(iter - left == 1)
                prev1 = true;
            else
                prev1 = false;
            left = iter;
            if(left == n) break;
            int right = left + 1;
            while(right < n && nums[right] == 1)
                ++right;
            int len = right - left;
            if(right < n - 1 || left > 0)
                ans = max(ans, len + 1);
            else
                ans = max(ans, len);
            if(prev1)
                ans = max(ans, len + 1 + prev_len);
            left = right;
            prev_len = len;
        }
        if(nums.back() == 0)
            ans = max(ans, 1 + prev_len);
        return ans;
    }
};
