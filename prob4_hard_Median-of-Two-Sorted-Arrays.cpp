// prob4: Median of Two Sorted Arrays

/*Description
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 * You may assume nums1 and nums2 cannot be both empty.
 */

/*
 * Example 1:
 * nums1 = [1, 3]
 * nums2 = [2]
 * The median is 2.0
 * Example 2:
 * nums1 = [1, 2]
 * nums2 = [3, 4]
  The median is (2 + 3)/2 = 2.5
 */

#include <vector>

using namespace std;

// 按照求第 k 大来想
// 二分在一个序列上所在的位置, 另一个序列上的位置对应可求，每次排除一半: 单序列上做二分
class Solution_1 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        if(n1 > n2) return findMedianSortedArrays(nums2, nums1);
        // n1 <= n2
        int n = n1 + n2;
        int k = (n + 1) / 2; // 找有序数组的第 k 大, 对应索引 k - 1;
        // n1 > 0
        int l1 = 0, r1 = n1; // 注意：n1 也是一组划分, 代表 nums1 的 n1 个都选了
        while(l1 <= r1)  // 循环内一定会找到，这个很关键，一些边界条件不用写了
        {
            // n1 = 0 时，l1 = 0, r1 = 0, 也必进循环，循环内一定找到答案
            int mid1 = l1 + (r1 - l1) / 2; // nums1 二分到索引 mid1, 有 mid1 个数, nums1[mid1] 本身属于右子序列
            int mid2 = k - mid1; // nums2 中要取 k - mid1 个数，nums2[mid2] 本身属于右子序列
            // 边界判断
            // 要么 mid1 取到 0, n 两个边界值之前已经找到答案
            // 要么 mid1 取到边界值 0, n 时是答案
            if(mid1 != 0 && nums1[mid1 - 1] > nums2[mid2])
                r1 = mid1 - 1;
            else if(mid1 != n1 && nums1[mid1] < nums2[mid2 - 1])
                l1 = mid1 + 1;
            else
            {
                // 找到答案，若取到边界值，则一定是答案
                double small;
                if(mid1 == 0) small = nums2[mid2 - 1];
                else if(mid2 == 0) small = nums1[mid1 - 1]; // 两个序列等长的情况
                else small = max(nums1[mid1 - 1], nums2[mid2 - 1]);
                if(n % 2 == 1) return small;
                double large;
                if(mid1 == n1) large = nums2[mid2];
                else if(mid2 == n2) large = nums1[mid1];
                else large = min(nums1[mid1], nums2[mid2]);
                return (small + large) / 2.0;
            }
        }
        return 0.0;
    }
};

// 按照求第 k 大来想
// 二分两个数组的第 k / 2 大，每次排除一半数，递归比较好写
class Solution_2 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        if(n1 > n2) return findMedianSortedArrays(nums2, nums1);
        int n = n1 + n2;
        int k = (n + 1) / 2; // 找有序数组的第 k 大, 对应索引 k - 1;
        if(n1 == 0)
        {
            if(n % 2 == 1)
                return (double)nums2[k - 1];
            else
                return ((double)nums2[k - 1] + nums2[k]) / 2;
        }
        int l1 = 0, l2 = 0;
        return _findKth(nums1, nums2, l1, l2, n1, n2, k);
    }
private:
    double _findKth(vector<int>& nums1, vector<int>& nums2, int l1, int l2, int n1, int n2, int k)
    {
        if(l1 == n1)
        {
            double small = (double)nums2[l2 + k - 1];
            if((n1 + n2) % 2 == 1)
                return small;
            else
            {
                double large = nums2[l2 + k];
                return (small + large) / 2.0;
            }
        }
        if(l2 == n2) // 保证了 nums1 长度 <= nums2 长度之后，这组判断条件可以去掉
        {
            double small = (double)nums1[l1 + k - 1];
            if((n1 + n2) % 2 == 1)
                return small;
            else
            {
                double large = nums1[l1 + k];
                return (small + large) / 2.0;
            }
        }
        if(k == 1)
        {
            if((n1 + n2) % 2 == 1)
                return (double)min(nums1[l1], nums2[l2]);
            else
            {
                double small, large;
                if(nums1[l1] <= nums2[l2])
                {
                    small = nums1[l1];
                    if(l1 + 1 < n1) large = min(nums1[l1 + 1], nums2[l2]);
                    else large = nums2[l2];
                }
                else
                {
                    small = nums2[l2];
                    if(l2 + 1 < n2) large = min(nums2[l2 + 1], nums1[l1]);
                    else large = nums1[l1];
                }
                return (small + large) / 2;
            }
        }
        int kk = k / 2;
        int i = l1 + kk - 1;
        if(i >= n1) i = n1 - 1;
        int j = l2 + kk - 1;
        if(j >= n2) i = n2 - 1;
        if(nums1[i] <= nums2[j])
            return _findKth(nums1, nums2, i + 1, l2, n1, n2, k - (i - l1 + 1));
        else
            return _findKth(nums1, nums2, l1, j + 1, n1, n2, k - (j - l2 + 1));
    }
};

