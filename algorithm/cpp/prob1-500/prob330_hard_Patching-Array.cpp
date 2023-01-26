// prob330: Patching Array

/*
 * https://leetcode-cn.com/problems/patching-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int m = nums.size();
        using ll = long long;
        ll miss = 1;
        int i = 0;
        int ans = 0;
        while(miss <= n)
        {
            if(i < m && nums[i] <= miss)
            {
                // 取到 [1, miss) 时尚未用到 nums[i]
                miss += nums[i];
                ++i;
            }
            else
            {
                miss *= 2;
                ++ans;
            }
        }
        return ans;
    }
};
