// prob75: Sort Colors

/*
 * Given an array with n objects colored red, white or blue, sort them in-place
 * so that objects of the same color are adjacent, with the colors in the order red, white and blue.
 * Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
 * Note: You are not suppose to use the library's sort function for this problem.
 */

/*
 * Example:
 * Input: [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 */

/*
 * Follow up:
 * A rather straight forward solution is a two-pass algorithm using counting sort.
 * First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
 * Could you come up with a one-pass algorithm using only constant space?
 */

#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        // _countingsort(nums);
        _twopointers(nums);
    }

private:
    // 基本计数排序
    void _countingsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        // 数据范围 0-2
        // 计数排序空间复杂度 O(N + K), K = 3
        int K = 3;
        vector<int> cnt(K, 0);
        for(int i = 0; i < n; ++i)
            ++cnt[nums[i]];

        for(int i = 0, k = 0; i < K; ++i)
            while(cnt[i] > 0)
            {
                nums[k++] = i;
                --cnt[i];
            }
    }

    // 双指针
    // 类似与单指针 partition 的操作
    void _twopointers(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        int left = 0, right = n - 1; // n >= 2, right >= 1
        // left 的左侧都是 0, right 的右侧都是 2
        for(int i = 0; i <= right;)
        {
            if(nums[i] == 0)
                _swap(nums, i++, left++);
            else if(nums[i] == 2)
                _swap(nums, i, right--);
            else
                ++i;
        }
    }

    void _swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
