// prob: Sliding Window Maximum

/*
 * Given an array nums, there is a sliding window of size k which is moving from the very
 * left of the array to the very right. You can only see the k numbers in the window.
 * Each time the sliding window moves right by one position. Return the max sliding window.
 */

/*
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
 * Output: [3,3,5,5,6,7]
 */

#include <vector>
#include <queue>
#include <set>
#include <deque>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// 1. 平衡树维护窗口内的值
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n <= k)
        {
            int mx = nums[0];
            for(int i = 1; i < n; ++i)
                mx = max(mx, nums[i]);
            return vector<int>({mx});
        }
        // 滑动 n - k 次
        // 0..k-1
        multiset<int> setting;
        vector<int> result;
        for(int i = 0; i < k; ++i)
            setting.insert(nums[i]);
        result.push_back(*(setting.rbegin()));
        for(int i = k; i < n; ++i)
        {
            setting.erase(setting.find(nums[i - k]));
            setting.insert(nums[i]);
            result.push_back(*setting.rbegin());
        }
        return result;
    }
};

// 2. 单调队列
class Solution_2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n <= k)
        {
            int mx = nums[0];
            for(int i = 1; i < n; ++i)
                mx = max(mx, nums[i]);
            return vector<int>({mx});
        }
        // 滑动 n - k 次
        // 0..k-1
        deque<int> dq;
        vector<int> result;
        for(int i = 0; i < k; ++i)
        {
            // 插入 i 前先出队
            while(!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            dq.push_back(i);
        }
        result.push_back(nums[dq.front()]);
        for(int i = k; i < n; ++i)
        {
            if(!dq.empty() && dq.front() <= i - k) dq.pop_front();
            while(!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            dq.push_back(i);
            result.push_back(nums[dq.front()]);
        }
        return result;
    }
};

// 3. DP
class Solution_3 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n <= k)
        {
            int mx = nums[0];
            for(int i = 1; i < n; ++i)
                mx = max(mx, nums[i]);
            return vector<int>({mx});
        }
        // 滑动 n - k 次
        // 0..k-1
        vector<int> left(n, 0);
        vector<int> right(n, 0);
        left[0] = nums[0];
        right[n - 1] = nums[n - 1];

        for(int i = 1; i < n; ++i)
        {
            if(i % k == 0)
                left[i] = nums[i];
            else
                left[i] = max(left[i - 1], nums[i]);
            int j = n - i - 1;
            if((j + 1) % k == 0)
                right[j] = nums[j];
            else
                right[j] = max(right[j + 1], nums[j]);
        }
        vector<int> result(n - k + 1);
        for(int i = 0; i < n - k + 1; ++i)
            result[i] = max(left[i + k - 1], right[i]);
        return result;
    }
};

// 堆，因为删除窗口最左边时候，需要索引 -> 最大索引堆
class MaxIndexHeap {
public:
    MaxIndexHeap(int n) {
        heap = vector<int>(n + 1, 0); // 数据数组 heap 从 1 开始
        indexes = vector<int>(n + 1, 0); // 数据数组 heap 从 1 开始
        reverses = vector<int>(n + 1, 0); // 数据数组 heap 从 1 开始
        count = 0;
        capacity = n;
    }

    int get_capacity() {
        return capacity;
    }

    bool empty() {
        return count == 0;
    }

    int size() {
        return count;
    }

    int top() {
        return heap[indexes[1]];
    }

    void pop() {
        if(empty()) return;
        swap(indexes[1], indexes[count]);
        reverses[indexes[1]] = 1;
        reverses[indexes[count]] = 0;
        --count;
        _push_down(1);
    }

    void remove(int index) {
        if(!contain(index)) return;
        swap(indexes[reverses[index + 1]], indexes[count]);
        int idx = reverses[index + 1]; // heap 中 index + 1 在 indexes 中的位置
        reverses[indexes[idx]] = idx;
        reverses[indexes[count]] = 0;
        --count;
        _push_down(idx);
    }

    void insert(int index, int x){ // push 改为 insert，既然用索引堆则插入必须带索引
        if(contain(index)) return; // 若index这个位置已经有值，则无动作
        // 若该位置以前有值，但后来被删除了，则该位置又可以插入了
        heap[index + 1] = x;
        indexes[count + 1] = index + 1;
        reverses[index + 1] = count + 1;
        ++count;
        _push_up(count);
    }

    void change(int index, int x) {
        // 索引堆多出来的关键功能
        heap[index + 1] = x;
        _push_up(reverses[index + 1]);
        _push_down(reverses[index + 1]);
    }

    bool contain(int index) {
        return reverses[index + 1] != 0;
    }

private:
    vector<int> heap;
    vector<int> indexes;
    vector<int> reverses;
    int count;
    int capacity;

    int _size() {
        return count;
    }

    // 堆的元素下标从1开始
    void _push_down(int u)
    {
        int size = _size();
        if(u > size) return;
        int t = u, left = u * 2, right = u * 2 + 1;
        if(left <= size && heap[indexes[left]] > heap[indexes[t]]) t = left;
        if(right <= size && heap[indexes[right]] > heap[indexes[t]]) t = right;
        if(t != u)
        {
            swap(indexes[u], indexes[t]);
            reverses[indexes[u]] = u;
            reverses[indexes[t]] = t;
            _push_down(t);
        }
    }

    void _push_up(int u)
    {
        int size = _size();
        if(u > size) return;
        while(u / 2 && heap[indexes[u / 2]] < heap[indexes[u]])
        {
            swap(indexes[u / 2], indexes[u]);
            reverses[indexes[u]] = u;
            reverses[indexes[u / 2]] = u / 2;
            u /= 2;
        }
    }
};

class Solution_4 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n <= k)
        {
            int mx = nums[0];
            for(int i = 1; i < n; ++i)
                mx = max(mx, nums[i]);
            return vector<int>({mx});
        }
        // 滑动 n - k 次
        // 0..k-1
        MaxIndexHeap heap(n);
        vector<int> result;
        for(int i = 0; i < k; ++i)
            heap.insert(i, nums[i]);
        result.push_back(heap.top());
        for(int i = k; i < n; ++i)
        {
            // 先 remove 再 insert, 有错误case 应该是 remove 实现的有问题
            // 暂未排查解决
            // heap.remove(i - k);
            // heap.insert(i, nums[i]);
            // change 的写法能过
            heap.change(i % k, nums[i]);
            result.push_back(heap.top());
        }
        return result;
    }
};

void unittest()
{
    // C++ 读测试文件
    ifstream fin("test/prob238_test0.txt");
    vector<int> a;
    int k = 0;
    string line;
    if(fin)
    {
        getline(fin, line);
        stringstream ss;
        ss << line;
        ss >> k;
        while(getline(fin, line))
        {
            stringstream ss;
            ss << line;
            if(!ss.eof())
            {
                int n;
                while(ss >> n)
                    a.push_back(n);
            }
        }
    }

    Solution_4 solution;
    vector<int> result = solution.maxSlidingWindow(a, k);
    ofstream fout("test/prob238_test0_result_2.txt");
    for(auto iter = result.begin(); iter != result.end(); ++iter)
    {
        fout << *iter << endl;
    }
}

int main()
{
    unittest();
}
