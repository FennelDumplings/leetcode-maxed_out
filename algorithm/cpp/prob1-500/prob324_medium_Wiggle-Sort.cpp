// prob324: Wiggle Sort

/*
 * Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
 * Note:
 * You may assume all input has valid answer.
 */

/*
 * Example 1:
 * Input: nums = [1, 5, 1, 1, 6, 4]
 * Output: One possible answer is [1, 4, 1, 5, 1, 6].
 * Example 2:
 * Input: nums = [1, 3, 2, 2, 3, 1]
 * Output: One possible answer is [2, 3, 1, 3, 1, 2].
 */

/*
 * Follow Up:
 * Can you do it in O(n) time and/or in-place with O(1) extra space?
 */

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <algorithm>

using namespace std;

// 普通排序，开一个辅助数组O(N)空间，来把排序后的数放到映射后的位置
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        make_heap(nums.begin(), nums.end(), less<int>());
        sort_heap(nums.begin(), nums.end(), less<int>());

        vector<int> tmp(n, 0);
        for(int i = 0; i < n; ++i)
            tmp[f(i, n)] = nums[i];
        nums = tmp;
    }

private:
    int f(int i, int n) // 坐标映射
    {
        // 假id(做排序的id) -> 真实应该放到的 id
        // 偶数长度 3,7,2,6,1,5,0,4
        // 奇数数长度 4,8,3,7,2,6,1,5,0
        // i <= (n - 1)/2 的放下面, i >= (n - 1)/2 + 1 放上面
        if(n % 2 == 0)
        {
            if(i <= (n - 1) / 2)
                return n - 2 - i * 2;
            else
                return n - 1 - (i - (n + 1) / 2) * 2;
        }
        else
        {
            if(i <= (n - 1) / 2)
                return n - 1 - i * 2;
            else
                return n - 2 - (i - (n + 1) / 2) * 2;
        }
    }
};

// 手写排序，排序的过程中直接映射，堆排，快排，归并在排序中映射比较难写，只写了插入排序，结果没问题但是TLE
class Solution_1 {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        insertsort(nums);
    }

private:
    void insertsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        for(int i = 1; i < n; ++i)
        {
            int tmp = nums[f(i, n)];
            int j;
            for(j = i - 1; j >= 0 && nums[f(j, n)] > tmp; --j)
                nums[f(j + 1, n)] = nums[f(j, n)];
            nums[f(j + 1, n)] = tmp;
        }
    }

    int f(int i, int n) // 坐标映射
    {
        // 假id(做排序的id) -> 真实应该放到的 id
        // 偶数长度 3,7,2,6,1,5,0,4
        // 奇数数长度 4,8,3,7,2,6,1,5,0
        // i <= (n - 1)/2 的放下面, i >= (n - 1)/2 + 1 放上面
        if(n % 2 == 0)
        {
            if(i <= (n - 1) / 2)
                return n - 2 - i * 2;
            else
                return n - 1 - (i - (n + 1) / 2) * 2;
        }
        else
        {
            if(i <= (n - 1) / 2)
                return n - 1 - i * 2;
            else
                return n - 2 - (i - (n + 1) / 2) * 2;
        }
    }
};

// 在优化1 的基础上，尝试写快排
// 在快排无 partition 版本和 swap 中有索引的位置都加上映射
class Solution_2 {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        quicksort(nums);
    }

private:
    void quicksort(vector<int> &nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        _quicksort3(nums, 0, n - 1);
    }

    // 快排最短模板, 不带 partition
    void _quicksort3(vector<int>& nums, int l, int r)
    {
        int n = nums.size();

        if(l >= r) return;
        int i = l - 1, j = r + 1, x = nums[f((l + r) >> 1, n)];// pivot 取中间点的值已经很好了，随机更好
        while(i < j)
        {
            do j--; while(nums[f(j, n)] > x);
            do i++; while(nums[f(i, n)] < x);
            if(i < j) _swap(nums, i, j);
            else _quicksort3(nums, l, j), _quicksort3(nums, j + 1, r); // 这一行代替了 partition
        }
    }

    int f(int i, int n) // 坐标映射
    {
        // 假id(做排序的id) -> 真实应该放到的 id
        // 偶数长度 3,7,2,6,1,5,0,4
        // 奇数数长度 4,8,3,7,2,6,1,5,0
        // i <= (n - 1)/2 的放下面, i >= (n - 1)/2 + 1 放上面
        if(n % 2 == 0)
        {
            if(i <= (n - 1) / 2)
                return n - 2 - i * 2;
            else
                return n - 1 - (i - (n + 1) / 2) * 2;
        }
        else
        {
            if(i <= (n - 1) / 2)
                return n - 1 - i * 2;
            else
                return n - 2 - (i - (n + 1) / 2) * 2;
        }
    }

    void _swap(vector<int>& nums, int i, int j)
    {
        int n = nums.size();
        int tmp = nums[f(i, n)];
        nums[f(i, n)] = nums[f(j, n)];
        nums[f(j, n)] = tmp;
    }
};

// 不需要全排序，只需要按照大于中位数，等于中位数，小于中位数排序, 变成了三色排序问题
// 需要先取到 kth_element, 这是一个专题，有基于快排和 BFPRT
// 这里直接用 kth_element;
class Solution_3 {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        _threecolorsort(nums);
    }

private:
    void _threecolorsort(vector<int>& nums)
    {
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        int mid = nums[n / 2];

        int left = 0, right = n - 1;
        int l = left, r = right, cur = left;
        // [left, l)   < mid
        // [l, cur)    = mid
        // [cur, r]    未处理
        // (r, right]  > mid
        while(cur <= r)
        {
            if(nums[f(cur, n)] < mid)
                _swap(nums, cur++, l++);
            else if(nums[f(cur, n)] == mid)
                ++cur;
            else
                _swap(nums, cur, r--);
        }
    }

    int f(int i, int n) // 坐标映射
    {
        // 假id(做排序的id) -> 真实应该放到的 id
        // 偶数长度 3,7,2,6,1,5,0,4
        // 奇数数长度 4,8,3,7,2,6,1,5,0
        // i <= (n - 1)/2 的放下面, i >= (n - 1)/2 + 1 放上面
        if(n % 2 == 0)
        {
            if(i <= (n - 1) / 2)
                return n - 2 - i * 2;
            else
                return n - 1 - (i - (n + 1) / 2) * 2;
        }
        else
        {
            if(i <= (n - 1) / 2)
                return n - 1 - i * 2;
            else
                return n - 2 - (i - (n + 1) / 2) * 2;
        }
    }

    void _swap(vector<int>& nums, int i, int j)
    {
        int n = nums.size();
        int tmp = nums[f(i, n)];
        nums[f(i, n)] = nums[f(j, n)];
        nums[f(j, n)] = tmp;
    }
};

// 简化 f(i, n) 然后用宏定义进一步减小代码量
class Solution_4 {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();

        auto midptr = nums.begin() + n / 2;
        nth_element(nums.begin(), midptr, nums.end());
        int mid = *midptr;

        #define A(i) nums[(1 + 2 * i) % (n | 1)]

        int l = 0, cur = 0, r = n - 1;
        while (cur <= r)
            if (A(cur) > mid)
                swap(A(l++), A(cur++));
            else if (A(cur) < mid)
                swap(A(cur), A(r--));
            else
                cur++;
    }
};

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> vec(nums);
        sort(vec.begin(), vec.end());
        for(int j = 0; j < n; ++j)
        {
            if(j & 1)
                nums[j] = vec[n - 1 - (j - 1) / 2];
            else
                nums[j] = vec[(n - 1) / 2 - j / 2];
        }
    }
};
