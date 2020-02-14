// prob88: Merge Sorted Array

/*
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
 * Note:
 * The number of elements initialized in nums1 and nums2 are m and n respectively.
 * You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.
 */

/*
 * Example:
 * Input:
 * nums1 = [1,2,3,0,0,0], m = 3
 * nums2 = [2,5,6],       n = 3
 * Output: [1,2,2,3,5,6]
 */

#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n == 0) return;
        if(m == 0)
        {
            for(int i = 0; i < n; ++i)
            {
                nums1[i] = nums2[i];
            }
            return;
        }
        for(int i = m - 1; i >= 0; --i)
            nums1[n + i] = nums1[i];
        int i = n, j = 0, k = 0;
        for(; i < m + n && j < n; ++k)
        {
            if(nums1[i] <= nums2[j])
            {
                nums1[k] = nums1[i];
                ++i;
            }
            else
            {
                nums1[k] = nums2[j];
                ++j;
            }
        }
        if(i == m + n)
            for(; j < n; ++j, ++k)
                nums1[k] = nums2[j];
        return;
    }
};
