// 面51: 数组中的逆序对

/*
 * 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
 */

/*
 * 示例 1:
 * 输入: [7,5,6,4]
 * 输出: 5
 */

#include <vector>

using namespace std;

// 在归并排序的归并阶段求逆序对个数
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 0;
        return _mergesort(nums, 0, n - 1);
    }

private:
    int _mergesort(vector<int>& nums, int left, int right)
    {
        int mid = left + (right - left) / 2;
        int res = 0;
        if(left == right) return 0;
        res += _mergesort(nums, left, mid);
        res += _mergesort(nums, mid + 1, right);
        res += _merge(nums, left, mid + 1, right);
        return res;
    }

    int _merge(vector<int>& nums, int left, int mid, int right)
    {
        int i = left, j = mid, k = 0;
        int res = 0;
        vector<int> tmp(right - left + 1, 0);
        while(i < mid && j <= right)
        {
            if(nums[i] > nums[j])
            {
                res += mid - i;
                tmp[k] = nums[j];
                ++k;
                ++j;
            }
            else
            {
                tmp[k] = nums[i];
                ++k;
                ++i;
            }
        }
        while(i < mid) tmp[k++] = nums[i++];
        while(j <= right) tmp[k++] = nums[j++];
        for(i = left, k = 0; i <= right; ++i, ++k)
            nums[i] = tmp[k];
        return res;
    }
};
