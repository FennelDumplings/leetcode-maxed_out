// prob209: Minimum Size Subarray Sum

/*
 * Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.
 */

/*
 * Example:
 * Input: s = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: the subarray [4,3] has the minimal length under the problem constraint.
 */

/*
 * Follow up:
 * If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
 */

#include <vector>

using namespace std;

// 双指针
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int result = 0;
        int sum = 0;
        int left = 0, right = 0;
        while(right < n)
        {
            if(left > right)
                left = right;
            if(sum + nums[right] < s)
            {
                sum += nums[right];
                ++right;
            }
            else
            {
                if(result > 0)
                    result = min(result, right -left + 1);
                else
                    result = right - left + 1;
                sum -= nums[left];
                ++left;
            }
        }
        return result;
    }
};

// 二分
class Solution_2 {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int left = 1, right = n;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            if(_check(nums, mid, s))
                right = mid - 1;
            else
                left = mid + 1;
        }
        if(left > n) return 0;
        return left;
    }

private:
    bool _check(const vector<int>& nums, int mid, int s)
    {
        int n = nums.size();
        int sum = 0;
        for(int i = 0; i < mid; ++i)
            sum += nums[i];
        if(sum >= s) return true;
        for(int i = 1; i + mid - 1 <= n - 1; ++i)
        {
            sum -= nums[i - 1];
            sum += nums[i + mid - 1];
            if(sum >= s)
                return true;
        }
        return false;
    }
};
