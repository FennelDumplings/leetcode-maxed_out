// interview53-2: 0～n-1中缺失的数字

/*
 * https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;
        // 找第一个 nums[mid] == mid + 1 的位置
        // [0, 1, 3]
        // [1, 2, 3]
        // [0, 1, 2]
        while(left < right)
        {
            int mid = (left + right) / 2;
            if(nums[mid] == mid)
                left = mid + 1;
            else
                right = mid;
        }
        if(left == n - 1 && nums[left] == left)
            return n;
        return left;
    }
};
