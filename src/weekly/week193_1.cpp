// 20200614
// 1. 一维数组的动态和

/*
 * 给你一个数组 nums 。数组「动态和」的计算公式为：runningSum[i] = sum(nums[0]…nums[i]) 。
 *
 * 请返回 nums 的动态和。
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> sums(n, 0);
        sums[0] = nums[0];
        for(int i = 1; i < n; ++i)
            sums[i] = sums[i - 1] + nums[i];
        return sums;

    }
};
