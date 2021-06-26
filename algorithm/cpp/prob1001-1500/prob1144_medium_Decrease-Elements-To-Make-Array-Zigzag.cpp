// prob1144: Decrease Elements To Make Array Zigzag

/*
 * Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
 * An array A is a zigzag array if either:
 * Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
 * OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
 * Return the minimum number of moves to transform the given array nums into a zigzag array.
 */

/*
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: 2
 * Explanation: We can decrease 2 to 0 or 3 to 1.
 * Example 2:
 * Input: nums = [9,6,1,6,2]
 * Output: 4
 */

/*
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 1000
 */

#include <vector>

using namespace std;

class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return 0;
        int result1 = 0; // 使得奇数位置元素大于相邻的答案
        int result2 = 0; // 使得偶数位置元素大于相邻的答案
        for(int i = 0; i < n; ++i)
        {
            if(i & 1)
            {
                int tmp = 0;
                tmp = max(tmp, nums[i] - nums[i - 1] + 1);
                if(i != n - 1)
                    tmp = max(tmp, nums[i] - nums[i + 1] + 1);
                result1 += tmp;
            }
            else
            {
                int tmp = 0;
                if(i != n - 1)
                    tmp = max(tmp, nums[i] - nums[i + 1] + 1);
                if(i != 0)
                    tmp = max(tmp, nums[i] - nums[i - 1] + 1);
                result2 += tmp;
            }
        }
        return min(result1, result2);
    }
};
