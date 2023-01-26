// prob665: Non-decreasing Array

/*
 * https://leetcode-cn.com/problems/non-decreasing-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2)
            return true;
        int prev = nums[0];
        int cnt = 0;
        for(int i = 1; i < n; ++i)
        {
            if(nums[i] >= prev)
            {
                prev = nums[i];
                continue;
            }
            if(cnt == 1) return false;
            ++cnt;
            if(i - 1 == 0 || nums[i - 2] <= nums[i])
            {
                // 改 nums[i - 1] 为 nums[i]
                prev = nums[i];
            }
        }
        return true;
    }
};
