// prob215: Kth Largest Element in an Array

/*
 * Find the kth largest element in an unsorted array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 */

/*
 * Example 1:
 * Input: [3,2,1,5,6,4] and k = 2
 * Output: 5
 * Example 2:
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4
 * Output: 4
 */

/*Note:
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 */

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 1) return nums[0];
        return heapk(nums, k);
        // return partition(nums, k, 0, n - 1);
    }

private:
    int partition(vector<int>& nums, int k, int left, int right)
    {
        // 在 nums 的 [left .. right] 中找第 k 大
        int randIdx = rand() % (right - left + 1) + left; // 随机选择 pivot
        _swap(nums, randIdx, left);
        int pivot = nums[left];
        int l = left, r = right;
        while(l < r)
        {
            while(l < r && nums[r] <= pivot)
                --r;
            if(l < r)
            {
                nums[l] = nums[r];
                ++l;
            }
            while(l < r && nums[l] >= pivot)
                ++l;
            if(l < r)
            {
                nums[r] = nums[l];
                --r;
            }
        }
        nums[l] = pivot;
        if(l == left + k - 1)
            return nums[l];
        else if(l < left + k - 1)
            return partition(nums, k - (l - left + 1), l + 1, right);
        else
            return partition(nums, k, left, l - 1);
    }

    void _swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    int heapk(vector<int>& nums, int k)
    {
        // 建堆 make_heap()
        // 添加 push_heap()
        // 删除 pop_heap()
        // 堆排序 sort_heap()
        vector<int> heap(k, 0);
        int n = nums.size();
        for(int i = 0; i < k; ++i)
            heap[i] = nums[i];
        make_heap(heap.begin(), heap.end(), greater<int>());
        pop_heap(heap.begin(), heap.end(), greater<int>());
        for(int i = k; i < n; ++i)
        {
            if(heap.back() < nums[i])
            {
                heap.pop_back();
                heap.push_back(nums[i]);
                push_heap(heap.begin(), heap.end(), greater<int>());
                pop_heap(heap.begin(), heap.end(), greater<int>());
            }
        }
        return heap.back();
    }
};
