// prob912: Sort an Array

/*
 * Given an array of integers nums, sort the array in ascending order.
 */

/*
 *Constraints:
 * 1 <= nums.length <= 50000
 * -50000 <= nums[i] <= 50000
 */

#include <vector>
#include <stack>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        insertsort(nums);
        shellsort(nums);
        selectsort(nums);
        heapsort(nums);
        bubblesort(nums);
        quicksort(nums);
        mergesort(nums);
        return nums;
    }

private:
    void insertsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        for(int i = 1; i < n; ++i)
        {
            int tmp = nums[i];
            int j = i - 1;
            for(; j >= 0 && nums[j] > tmp; --j)
                nums[j + 1] = nums[j];
            nums[j + 1] = tmp;
        }
    }

    void shellsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        for(int step = n / 2; step > 0; step /= 2)
        {
            for(int i = step; i < n; ++i)
            {
                int tmp = nums[i];
                int j = i - step;
                for(; j >= 0 && nums[j] > tmp; j -= step)
                    nums[j + step] = nums[j];
                nums[j + step] = tmp;
            }
        }
    }

    void selectsort(vector<int> &nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        for(int i = 0; i < n; ++i)
        {
            int tmp = nums[i];
            int min_index = i;
            for(int j = i + 1; j < n; ++j)
            {
                if(nums[j] < tmp)
                {
                    tmp = nums[j];
                    min_index = j;
                }
            }
            swap(nums, i, min_index);
        }
    }

    void swap(vector<int> &nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    void heapsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        int i;
        for(i = n / 2 - 1; i >= 0; --i)
        {
            percolateDown(nums, i, n);
        }
        for(i = n - 1; i > 0; --i)
        {
            swap(nums, 0, i);
            percolateDown(nums, 0, i);
        }
    }

    void percolateDown(vector<int>& nums, int hole, int n)
    {
        int child;
        int tmp = nums[hole];
        for(; hole * 2 + 1 < n; hole = child)
        {
            child = hole * 2 + 1;
            if(child != n - 1 && nums[child + 1] > nums[child])
                ++child;
            if(nums[child] > tmp)
                nums[hole] = nums[child];
            else
                break;
        }
        nums[hole] = tmp;
    }

    void bubblesort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        int i, j;
        bool flag; // 记录一趟起泡时有无交换
        for(i = 1; i < n; ++i)
        {
            flag = false;
            for(j = 0; j < n - i; ++j) // 第 i 次起泡
            {
                if(nums[j + 1] < nums[j])
                {
                    swap(nums, j, j + 1);
                    flag = true;
                }
            }
            if(!flag) break;
        }
    }

    void quicksort(vector<int> &nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        _quicksort2(nums, 0, n - 1);
    }

    void _quicksort1(vector<int> &nums, int low, int high)
    {
        // 递归
        int mid;
        if(low >= high) return;
        mid = divide1(nums, low, high); // 分治的划分点 mid 不一定是数组中点，而是与 pivot 元素具体值有关系
        _quicksort1(nums, low, mid - 1); // 排序左边一半
        _quicksort1(nums, mid + 1, high);
    }

    void _quicksort2(vector<int>& nums, int low, int high)
    {
        // 非递归版快排
        stack<int> st;
        st.push(low);
        st.push(high);
        while(!st.empty()){
            int r = st.top();
            st.pop();
            int l = st.top();
            st.pop();
            if(l >= r) continue;
            int mid = divide1(nums, l, r);
            st.push(l);
            st.push(mid - 1);
            st.push(mid + 1);
            st.push(r);
        }
    }

    int divide1(vector<int>& nums, int low, int high)
    {
        // 单指针划分
        int randIdx = rand() % (high - low + 1) + low; // 随机选择 pivot
        swap(nums, randIdx, low);
        int pivot = nums[low]; // 标准元素, 支点元素取最左边
        int index = high;
        for(int i = high; i > low; --i)
        {
            if(nums[i] >= pivot)
            {
                swap(nums, i, index);
                --index;
            }
        }
        swap(nums, index, low);
        return index;
    }

    int divide2(vector<int>& nums, int low, int high)
    {
        // 双指针划分
        int randIdx = rand() % (high - low + 1) + low; // 随机选择 pivot
        swap(nums, randIdx, low);
        int pivot = nums[low]; // 标准元素, 支点元素取最左边
        while(low < high)
        {
            while(low < high && nums[high] >= pivot)
                --high;
            if(low < high)
            {
                nums[low] = nums[high];
                ++low;
            }
            while(low < high && nums[low] <= pivot)
                ++low;
            if(low < high)
            {
                nums[high] = nums[low];
                --high;
            }
        }
        nums[low] = pivot;
        return low;
    }

    void mergesort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        _mergesort(nums, 0, n - 1);
    }

    void _mergesort(vector<int>& nums, int low, int high)
    {
        int mid = low + (high - low) / 2;
        if(low == high) return;
        _mergesort(nums, low, mid);
        _mergesort(nums, mid + 1, high);
        _merge(nums, low, mid + 1, high); // 归并左右两个有序表
    }

    void _merge(vector<int>& nums, int low, int mid, int high)
    {
        vector<int> tmp(high - low + 1, 0);
        int i = low, j = mid, k = 0;
        while(i < mid && j <= high)
        {
            if(nums[i] < nums[j])
            {
                tmp[k] = nums[i];
                ++k;
                ++i;
            }
            else
            {
                tmp[k] = nums[j];
                ++k;
                ++j;
            }
        }
        while(i < mid) tmp[k++] = nums[i++];
        while(j <= high) tmp[k++] = nums[j++];
        for(i = 0, k = low; k <= high;)
            nums[k++] = tmp[i++];
    }

};
