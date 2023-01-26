// prob713: subarray-product-less-than-k

/*
 * Your are given an array of positive integers nums.
 * Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.
 */

/*
 * Example 1:
 * Input: nums = [10, 5, 2, 6], k = 100
 * Output: 8
 * Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
 * Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 */

/*
 * Note:
 * 0 < nums.length <= 50000.
 * 0 < nums[i] < 1000.
 * 0 <= k < 10^6.
 */

#include <vector>

using namespace std;

// 300ms
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int left  = 0, right = 0;
        int result = 0;
        int cur_len = 0;
        int cum_product = 1;
        while(right < n)
        {
            while(right < n && cum_product * nums[right] < k)
                cum_product *= nums[right++];
            if(right - left >= cur_len) // right 有前进
            {
                result -= _counting(cur_len);
                cur_len = right - left;
                result += _counting(cur_len);
            }
            if(left < right)
            {
                cum_product /= nums[left++];
                --cur_len;
            }
            else if(left == right)
            {
                // 此时 cur_len=0, cum_product=1
                ++left;
                ++right;
            }
        }
        return result;
    }

private:
    int _counting(int n)
    {
        if((n & 1) == 0)
            return n / 2 * (n - 1) + n;
        else
            return (n - 1) / 2 * n + n;
    }
};

// 优化版
// 130ms
class Solution_2 {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int left  = 0, right = 0;
        int result = 0;
        int cum_product = 1;
        while(left < n)
        {
            while(right < n && cum_product * nums[right] < k)
                cum_product *= nums[right++];
            if(left < right)
            {
                result += right - left;
                cum_product /= nums[left++];
            }
            else if(left == right)
            {
                ++left;
                ++right;
            }
        }
        return result;
    }
};

// 优化版另一种写法
class Solution_3 {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        int curProduct = 1;

        for (int i = 0, j = 0; i < n; i++) {
            curProduct *= nums[i];
            while (j <= i && curProduct >= k) {
                curProduct /= nums[j];
                j++;
            }
            ans += i - j + 1;
        }
        return ans;
    }
};
