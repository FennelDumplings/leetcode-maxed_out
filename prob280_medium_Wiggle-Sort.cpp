// prob280: Wiggle Sort

/*
 * Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
 */

/*
 * Example:
 *
 * Input: nums = [3,5,2,1,6,4]
 * Output: One possible answer is [3,5,1,6,2,4]
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// 自己实现堆
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        nums.push_back(nums[0]);
        int size = n;
        _make_heap(nums, n);
        // 出堆 n/2 次
        for(int i = 0; i < n / 2; ++i)
        {
            _swap(nums, 1, n - i);
            _push_down(nums, 1, --size);
        }

        for(int i = 0; i < n / 2; ++i)
            _swap(nums, 2 + 2 * i, (n + 1) / 2 + 1 + i);
        for(int i = 0; i < n; ++i)
            nums[i] = nums[i + 1];
        nums.pop_back();
    }

private:
    void _make_heap(vector<int>& heap, int size)
    {
        // heap 数组的元素已经是从 1 开始，到 size
        for(int i = 1; i <= size; ++i)
            _push_up(heap, i, size);
    }

    void _push_down(vector<int>& heap, int i, int size)
    {
        int father = i;
        int iter = i, left = 2 * i, right = 2 * i + 1;
        if(left <= size && heap[left] > heap[iter]) iter = left;
        if(right <= size && heap[right] > heap[iter]) iter = right;
        if(iter != father)
        {
            _swap(heap, iter, father);
            _push_down(heap, iter, size);
        }
    }

    void _push_up(vector<int>& heap, int i, int size)
    {
        if(i > size) return;
        int child = i, father = child / 2;
        if(father >= 1 && heap[father] < heap[child])
        {
            _swap(heap, father, child);
            _push_up(heap, father, size);
        }
    }

    void _insert(vector<int>& heap, int size, int item)
    {
        heap[++size] = item;
        _push_up(heap, size, size);
    }

    void _remove_top(vector<int>& heap, int size)
    {
        _swap(heap, 1, size--);
        _push_down(heap, 1, size);
    }

    void _swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};

// 使用STL的堆
class Solution_2 {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        make_heap(nums.begin(), nums.end(), less<int>());
        // 出堆 n/2 次
        for(int i = 0; i < n / 2; ++i)
            pop_heap(nums.begin(), nums.end() - i, less<int>());

        for(int i = 0; i < n / 2; ++i)
            _swap(nums, 1 + 2 * i, (n + 1) / 2 + i);
    }

private:
    void _swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};

// 一趟遍历解决, 对直觉的验证
class Solution_3 {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        // n >= 2
        for(int i = 1; i < n; ++i)
        {
            // if(i % 2 == 1 && nums[i] < nums[i - 1])
            //     _swap(nums, i, i - 1);
            // if(i % 2 == 0 && nums[i] > nums[i - 1])
            //     _swap(nums, i, i - 1);

            // 极致简化
            if ((i % 2 == 0) == (nums[i] > nums[i + 1]))
                _swap(nums, i, i - 1);
        }
    }

private:
    void _swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
