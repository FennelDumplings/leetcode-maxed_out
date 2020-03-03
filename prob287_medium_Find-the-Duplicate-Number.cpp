// prob287: Find the Duplicate Number

/*
 * Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive),
 * prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.
 */

/*
 * Example 1:
 * Input: [1,3,4,2,2]
 * Output: 2
 * Example 2:
 * Input: [3,1,3,4,2]
 * Output: 3
 */

/*
 * Note:
 * You must not modify the array (assume the array is read only).
 * You must use only constant, O(1) extra space.
 * Your runtime complexity should be less than O(n2).
 * There is only one duplicate number in the array, but it could be repeated more than once.
 */

#include <vector>

using namespace std;

// 快慢指针法
// 为什么从 nums[0] 出发的环才是重复数字需要画图，不从 nums[0] 出发的也会有环
// O(N)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        while(fast == 0 || slow != fast)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        for(int i = 0; i != slow; i = nums[i])
            slow = nums[slow];
        return slow;
    }
};

// 二分，更通用的方法
// O(NlogN)
class Solution_2 {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        // 数字在 1 ~ n-1 之间
        int left = 1, right = n - 1;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            int cnt = 0;
            for(int num: nums)
                if(num <= mid)
                    ++cnt;
            if(cnt > mid)
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};

