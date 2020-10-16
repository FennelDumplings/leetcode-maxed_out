// prob1558: Minimum Numbers of Function Calls to Make Target Array

/*
 * https://leetcode-cn.com/problems/minimum-numbers-of-function-calls-to-make-target-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        bool flag = true;
        while(flag)
        {
            flag = false;
            for(int i = 0; i < n; ++i)
            {
                if(nums[i] > 0)
                    flag = true;
                if(nums[i] & 1)
                {
                    --nums[i];
                    ++ans;
                }
            }
            bool flag2 = false;
            for(int i = 0; i < n; ++i)
            {
                if(nums[i] > 0)
                {
                    flag2 = true;
                    nums[i] /= 2;
                }
            }
            if(flag2)
                ++ans;
        }
        return ans;
    }
};
