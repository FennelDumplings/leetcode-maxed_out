// prob213: House Robber II

/*
 * 与 prob198 相同，仅有两个端点的房子视为相邻这一个区别
 */

#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        return max(solve(nums, 0, n - 2), solve(nums, 1, n - 1));
    }

private:
    int solve(vector<int>& nums, int left, int right)
    {
        int n = right - left + 1;
        if(n == 2) return max(nums[left], nums[right]);
        int mx0 = nums[left], mx1 = nums[left + 1], mx2 = nums[left] + nums[left + 2];
        int result = max(mx1, mx2);
        for(int i = left + 3; i <= right; ++i)
        {
            int mx = nums[i] + max(mx0, mx1);
            result = max(result, mx);
            mx0 = mx1;
            mx1 = mx2;
            mx2 = mx;
        }
        return result;
    }
};
