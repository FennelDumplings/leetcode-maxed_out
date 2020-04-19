// prob53: Maximum Subarray

/* description:
 * Given an integer array nums, find the contiguous subarray (containing at least one number)
 * which has the largest sum and return its sum.
 */

/*
 * Example:
 * Input: [-2,1,-3,4,-1,2,1,-5,4],
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 */


#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // 默认 nums 不为空
        int n = nums.size();
        int sum = max(0, nums[0]); // 当前的子串和
        int mx = nums[0]; // 数组中的最大的数
        int ans = nums[0]; // 当前的最大子串和
        for(int i = 1; i < n; ++i)
        {
            mx = max(mx, nums[i]);

            if(nums[i] > 0)
            {
                sum += nums[i];
                ans = max(ans, sum);
            }
            else
            {
                if(sum + nums[i] >= 0)
                    sum += nums[i];
                else
                    sum = 0;
            }
        }
        ans = max(mx, ans);
        return ans;
    }
};

// 代码等价变形
class Solution_2 {
public:
    int maxSubArray(vector<int>& nums) {
        // 默认 nums 不为空
        int n = nums.size();
        int sum = 0; // 当前的子串和
        int ans = INT_MIN; // 当前的最大子串和
        for(int i = 0; i < n; ++i)
        {
            sum = max(sum + nums[i], nums[i]);
            ans = max(ans, sum);
        }
        return ans;
    }
};

// 分治法
class Solution_3 {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        return _maxSubArray(nums, 0, n); // [0, n)
    }

private:
    int _maxSubArray(const vector<int> &nums, int left, int right)
    {
        // [left, right)
        int length = right - left;
        int mid = (length + 1) / 2 + left;

        // 递归终止
        if(length == 1) return nums[left];

        // 至少两个元素
        int left_result = _maxSubArray(nums, left, mid);
        int right_result = _maxSubArray(nums, mid, right);

        // mid_result 一定包含 nums[mid] 和 nums[mid - 1]
        int mid_result = nums[mid] + nums[mid - 1]; // 初始化
        int right_sum = 0;
        int right_maxsum = 0;
        for(int i = mid + 1; i < right; ++i)
        {
            right_sum += nums[i];
            right_maxsum = max(right_maxsum, right_sum);
        }
        int left_sum = 0;
        int left_maxsum = 0;
        for(int i = mid - 2; i >= left; --i)
        {
            left_sum += nums[i];
            left_maxsum = max(left_maxsum, left_sum);
        }
        mid_result = mid_result + left_maxsum + right_maxsum;

        return max(max(left_result, right_result), mid_result);
    }
};
