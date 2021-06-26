// prob1567: Maximum Length of Subarray With Positive Product

/*
 * https://leetcode-cn.com/problems/maximum-length-of-subarray-with-positive-product/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        int left_odd = -1, left_even = -1;
        int cnt = 0;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] == 0)
            {
                left_odd = -1;
                left_even = i;
                cnt = 0;
                continue;
            }
            if(nums[i] < 0)
                cnt ^= 1;
            if(left_odd == -1 && nums[i] < 0 && (cnt & 1) == 1)
            {
                left_odd = i;
            }
            if(cnt & 1)
            {
                if(left_odd != -1)
                    ans = max(ans, i - left_odd);
            }
            else
            {
                ans = max(ans, i - left_even);
            }
        }
        return ans;
    }
};
