// prob581: Shortest Unsorted Continuous Subarray

/*
 * Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.
 * You need to find the shortest such subarray and output its length.
 */

/*
 * Example 1:
 * Input: [2, 6, 4, 8, 10, 9, 15]
 * Output: 5
 * Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
 */

/*
 * Note:
 * Then length of the input array is in range [1, 10,000].
 * The input array may contain duplicates, so ascending order here means <=.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 0;
        int left = 0;
        int maxx = nums[left];
        int j = 0;
        while(left < n)
        {
            if(nums[left] < maxx)
                j = left;
            else if(nums[left] > maxx)
                maxx = nums[left];
            ++left;
        }
        int right = n - 1;
        int minx = nums[right];
        int i = n - 1;
        while(right >= 0)
        {
            if(nums[right] > minx)
                i = right;
            else if(nums[right] < minx)
                minx = nums[right];
            --right;
        }
        int result = j - i + 1;
        if(result > 1)
            return result;
        return 0;
    }
};
