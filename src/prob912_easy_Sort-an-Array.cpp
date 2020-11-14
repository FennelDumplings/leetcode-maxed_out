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
#include <iostream>

using namespace std;

class Solution_2 {
public:
    vector<int> sortArray(vector<int>& nums) {
        // sort(nums.begin(), nums.end());
        // insertsort(nums);
        // shellsort(nums);
        // selectsort(nums);
        // heapsort(nums);
        // bubblesort(nums);
        // quicksort(nums);
        // mergesort(nums);
        // countingsort(nums);
        // bucketsort(nums);
        // radixsort(nums);
        cocktailsort(nums);
        return nums;
    }

private:
    // 插入
    void insertsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        for(int i = 1; i < n; ++i)
        {
            int tmp = nums[i];
            int j;
            for(j = i - 1; j >= 0 && nums[j] > tmp; --j)
                nums[j + 1] = nums[j];
            nums[j + 1] = tmp;
        }
    }

    // 希尔
    // 确定比快排慢，基本被淘汰
    void shellsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        // 选取 step 与算法复杂度证明有关，参考算法导论
        int step = 1;
        while(step < n / 3)
            step = step * 3 + 1;

        // for(int step = n / 2; step > 0; step /= 2)
        for(; step > 0; step /= 3)
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

    // 选择
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
                // i ~ n 最小的数放到 i 位置
                if(nums[j] < tmp)
                {
                    tmp = nums[j];
                    min_index = j;
                }
            }
            _swap(nums, i, min_index);
        }
    }

    // 堆排序
    void heapsort(vector<int>& nums)
    {
        // heapsort1(nums);
        heapsort2(nums);
    }

    void heapsort1(vector<int>& nums)
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
            _swap(nums, 0, i);
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

    // 堆排序更好的模板, 从小到大排， 大顶堆
    void heapsort2(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        _heapsort(nums, n);
    }

    // 堆的元素下标从1开始
    void push_down(vector<int>& heap, int size, int u)
    {
        int t = u, left = u * 2, right = u * 2 + 1;
        if(left <= size && heap[left] > heap[t]) t = left;
        if(right <= size && heap[right] > heap[t]) t = right;
        if(t != u)
        {
            swap(heap[u], heap[t]);
            push_down(heap, size, t);
        }
    }

    void push_up(vector<int>& heap, int size, int u)
    {
        if(u > size) return;
        while(u / 2 && heap[u / 2] < heap[u])
        {
            swap(heap[u / 2], heap[u]);
            u /= 2;
        }
    }

    void insert(vector<int>& heap, int size, int x)
    {
        heap[++size] = x;
        push_up(heap, size, x);
    }

    void remove_top(vector<int>& heap, int size)
    {
        heap[1] = heap[size--];
        push_down(heap, size, 1);
    }

    void _heapsort(vector<int>& heap, int size)
    {
        heap.push_back(0);
        int n = size;
        for(int i = n - 1; i >= 0; --i) heap[i + 1] = heap[i];
        for(int i = 1; i <= size; ++i) push_up(heap, size, i); // 时间复杂度 O(N) 不是 O(NlogN)
        for(int i = n; i >= 1; --i)
        {
            swap(heap[1], heap[size--]);
            push_down(heap, size, 1);
        }
        for(int i = 0; i < n; ++i) heap[i] = heap[i + 1];
        heap.pop_back();
    }

    // 冒泡
    void bubblesort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        int i, j;
        bool flag; // 记录一趟起泡时有无交换, 冒泡排序的基本优化
        // for(i = 1; i < n; ++i)
        for(i = n - 1; i >= 1; --i)
        {
            flag = false;
            // for(j = 0; j < n - i; ++j) // 第 i 次起泡
            for(j = 0; j <= i - 1; ++j) // 第 i 次起泡
            {
                if(nums[j + 1] < nums[j])
                {
                    _swap(nums, j, j + 1);
                    flag = true;
                }
            }
            if(!flag) break;
        }
    }

    // 快排
    void quicksort(vector<int> &nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        _quicksort3(nums, 0, n - 1);
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
        _swap(nums, randIdx, low);
        int pivot = nums[low]; // 标准元素, 支点元素取最左边
        int index = high;
        for(int i = high; i > low; --i)
        {
            if(nums[i] >= pivot)
            {
                _swap(nums, i, index);
                --index;
            }
        }
        _swap(nums, index, low);
        return index;
    }

    int divide2(vector<int>& nums, int low, int high)
    {
        // 双指针划分
        int randIdx = rand() % (high - low + 1) + low; // 随机选择 pivot
        _swap(nums, randIdx, low);
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

    // 快排最短模板, 不带 partition
    void _quicksort3(vector<int>& nums, int l, int r)
    {
        if(l >= r) return;
        int i = l - 1, j = r + 1, x = nums[(l + r) >> 1];// pivot 取中间点的值已经很好了，随机更好
        while(i < j)
        {
            do j--; while(nums[j] > x);
            do i++; while(nums[i] < x);
            if(i < j) _swap(nums, i, j);
            else _quicksort3(nums, l, j), _quicksort3(nums, j + 1, r); // 这一行代替了 partition
        }
    }

    // 归并, 两种实现方式, 自顶向下
    void mergesort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        vector<int> tmp(n, 0);
        // _mergesort_topdown(nums, 0, n - 1);
        _mergesort_buttomup(nums, n);
    }

    // 自顶向下
    void _mergesort_topdown(vector<int>& nums, int low, int high)
    {
        int mid = low + (high - low) / 2;
        if(low == high) return;
        _mergesort_topdown(nums, low, mid);
        _mergesort_topdown(nums, mid + 1, high);
        _merge(nums, low, mid + 1, high); // 归并左右两个有序表
    }

    // 自底向上
    void _mergesort_buttomup(vector<int >& nums, int n)
    {
        // vector<int> tmp(n, 0);
        int left, size;
        for(size = 1; size < n; size *= 2)
            for(left = 0; left < n - size; left += 2 * size)
            {
                int right = min(left + 2 * size - 1, n - 1);
                int mid = left + size - 1; // mid > right 时，直接就是半边有序的
                _merge(nums, left, mid + 1, right);
            }
    }

    // 非常经典的归并操作
    // 类似问题例如链表的二路归并，多路归并等
    void _merge(vector<int>& nums, int low, int mid, int high)
    {
        // 归并时候的辅助数组
        vector<int> tmp(high - low + 1, 0);
        // 下面这么写的话，往辅助数组里插入需要 push_back
        // static vector<int> tmp;
        // tmp.clear();

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
        for(k = 0, i = low; i <= high; ++k, ++i)
            nums[i] = tmp[k];
    }

    // 鸡尾酒排序
    void cocktailsort(vector<int>& nums)
    {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while(left < right){
            //前半轮，将最大元素放到后面
            for(int i = left; i < right; i++)
                if(nums[i] > nums[i + 1])
                    _swap(nums, i, i + 1);
            right--;
            //后半轮，将最小元素放到前面
            for(int i = right; i > left; i--)
                if(nums[i] < nums[i - 1])
                    _swap(nums, i, i - 1);
            left++;
        }
    }

    void _swap(vector<int> &nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    // 计数排序,
    // 1 <= A.length <= 10000
    // -50000 <= A[i] <= 50000
    void countingsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        // 范围 [-50000, 50000] 映射到[0, 100000]
        for(int i = 0; i < n; ++i)
            nums[i] += 50000;
        int m = 100001; //[0, 100000]
        // _countingsort1(nums, m);
        _countingsort2(nums, m);
        for(int i = 0; i < n; ++i) // 减回来
            nums[i] -= 50000;
    }

    // 不保证稳定, 也叫假计数排序
    void _countingsort1(vector<int>& nums, int m)
    {
        int n = nums.size();
        vector<int> cnt(m + 1, 0);
        for(int i = 0; i < n; ++i) cnt[nums[i]]++;

        for(int i = 0, k = 0; i <= m; ++i)
        {
            while(cnt[i]){
                nums[k++] = i;
                cnt[i]--;
            }
        }
    }

    // 保证稳定, 借助 cnt 数组的前缀和
    void _countingsort2(vector<int>& nums, int m)
    {
        int n = nums.size();
        vector<int> cnt(m + 1, 0);
        for(int i = 0; i < n; ++i) cnt[nums[i]]++;

        vector<int> presum_cnt(m + 2, 0);
        for(int i = 1; i < m + 2; ++i)
            presum_cnt[i] = presum_cnt[i - 1] + cnt[i - 1];
        vector<int> tmp(nums.begin(), nums.end()); // nums 的副本

        for(int i = n - 1; i >= 0; --i)
            nums[--presum_cnt[tmp[i]]] = tmp[i];
    }

    // 桶排序
    // 范围 [-50000, 50000] 映射到[0, 100000]
    void bucketsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        int m = 11; // m 个桶, 每个桶里 100000/m 个数, 100000 单独是一个桶
        _bucketsort2(nums, m);
    }

    // 用 vector 指针的 vector 存桶
    void _bucketsort(vector<int>& nums, int m)
    {
        // 数字 num -> 桶编号 i
        // (num + 50000) / 1000
        vector<vector<int>* > buckets(m, nullptr);
        for(int i = 0; i < m; ++i)
            buckets[i] = new vector<int>();

        int n = nums.size();
        for(int i = 0; i < n; ++i)
            buckets[(nums[i] + 50000) / (100000 / (m - 1))] -> push_back(nums[i]);

        for(int i = 0; i < m; ++i)
            quicksort(*(buckets[i]));

        int iter = 0;
        for(vector<int> *bucket: buckets)
            for(int num: *bucket)
                nums[iter++] = num;

        for(int i = 0; i < m; ++i)
            delete buckets[i];
    }

    // 用vector的vector 存桶
    void _bucketsort2(vector<int>& nums, int m)
    {
        // 数字 num -> 桶编号 i
        // (num + 50000) / 1000
        vector<vector<int> > buckets(m);

        int n = nums.size();
        for(int i = 0; i < n; ++i)
            buckets[(nums[i] + 50000) / (100000 / (m - 1))].push_back(nums[i]);

        for(int i = 0; i < m; ++i)
            quicksort(buckets[i]);

        int iter = 0;
        for(vector<int> bucket: buckets)
            for(int num: bucket)
                nums[iter++] = num;
    }

    // 基数排序, 只能对正数用(以下代码用在含负数的数组报错)
    // 且O(N)的常数较大，实际比 O(NlogN) 慢, 很少用
    void radixsort(vector<int>& nums)
    {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        for(int i = 0; i < n; ++i)
            nums[i] += 50000;
        _radixsort(nums);
        for(int i = 0; i < n; ++i) // 减回来
            nums[i] -= 50000;

    }

    void _radixsort(vector<int>& nums)
    {
        int n = nums.size();
        // 定义桶
        vector<vector<int> > cnt(10); // 数位一共有 10 种, 10 个桶
        for(int i = 0; i < 10; ++i)
        {
            for(int j = 0; j < 10; ++j) cnt[j].clear();

            for(int j = 0; j < n; ++j)
                cnt[get(nums[j], i)].push_back(nums[j]);

            for(int j = 0, k = 0; j < 10; ++j)
                for(int num: cnt[j])
                    nums[k++] = num;
        }

    }

    int get(int x, int i) // 返回 x 的第 i 位
    {
        while(i--) x /= 10;
        return x % 10;
    }
};

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> indexes(n);
        for(int i = 1; i < n; ++i)
            indexes[i] = i;
        Cmp cmp(&nums);
        sort(indexes.begin(), indexes.end(), cmp);
        vector<int> result;
        for(int i: indexes)
            result.push_back(nums[i]);
        return result;
    }

private:
    struct Cmp
    {
        vector<int> *data;
        Cmp(vector<int>* const nums)
        {
            data = nums;
        }
        bool operator()(const int& i1, const int& i2) const
        {
            return data -> at(i1) < data -> at(i2);
        }
    };
};
