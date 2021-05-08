// prob719： Find K-th Smallest Pair Distance

/*
 * Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/find-k-th-smallest-pair-distance
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/*
 * Example 1:
 * Input:
 * nums = [1,3,1]
 * k = 1
 * Output: 0
 * Explanation:
 * Here are all the pairs:
 * (1,3) -> 2
 * (1,1) -> 0
 * (3,1) -> 2
 * Then the 1st smallest distance pair is (1,1), and its distance is 0.
 */

/*
 * Note:
 * 2 <= len(nums) <= 10000.
 * 0 <= nums[i] < 1000000.
 * 1 <= k <= len(nums) * (len(nums) - 1) / 2.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int right = nums[n - 1] - nums[0], left = 0;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            int y = check(nums, mid);
            // y 为 dist 距离可以取到的最大的排名
            if(y < k)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

private:
    int check(const vector<int>& nums, int dist)
    {
        int n = nums.size();
        int left = 0;
        int right = 0;
        int result = 0;
        while(left < n)
        {
            int prev_right = right;
            int cur_left_val = nums[left], max_right_val = cur_left_val + dist;
            while(right < n && nums[right] <= max_right_val)
                ++right;
            int cnt = right - left;
            int duplicate = prev_right - left;
            result += cnt * (cnt - 1) / 2;
            // 容斥原理
            if(duplicate > 1)
                result -= duplicate * (duplicate - 1) / 2;
            while(left < n && nums[left] == cur_left_val)
                ++left;
        }
        return result;
    }
};

