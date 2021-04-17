// prob480: Sliding Window Median

/*
 * Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value.
 * So the median is the mean of the two middle value.
 * Examples:
 * [2,3,4] , the median is 3
 * [2,3], the median is (2 + 3) / 2 = 2.5
 * Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
 * You can only see the k numbers in the window. Each time the sliding window moves right by one position.
 * Your job is to output the median array for each window in the original array.
 */

/*
 * Note:
 * You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
 * Answers within 10^-5 of the actual value will be accepted as correct.
 */

#include <vector>
#include <set>
#include <queue>
#include <unordered_map>

using namespace std;

// multiset 用法
class Solution_2 {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k)
    {
        multiset<int> setting(nums.begin(), nums.begin() + k);
        auto it_mid = next(setting.begin(), (k - 1) / 2);

        int n = nums.size();
        vector<double> result(n - k + 1);
        result[0] = (((double)(*it_mid) + *next(it_mid, 1 - k % 2)) * 0.5);
        for (int i = k; i < n; ++i)
        {
            setting.insert(nums[i]);
            if (nums[i] < *it_mid)
                --it_mid;

            if (nums[i - k] <= *it_mid)
                ++it_mid;
            setting.erase(setting.lower_bound(nums[i - k]));

            result[i - k + 1] = (((double)(*it_mid) + *next(it_mid, 1 - k % 2)) * 0.5);
        }
        return result;
    }
};

// 双堆模式
class Solution_2 {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        unordered_map<int, int> mapping;
        priority_queue<int> max_heap; // 大顶堆，存较小的一半
        priority_queue<int, vector<int>, greater<int> > min_heap; // 小顶堆，存较大的一半

        int i = 0; // 划窗的当前值

        // 堆的初始化
        while(i < k)
        {
            max_heap.push(nums[i]);
            ++i;
        }
        for(int j = 0; j < k / 2; ++j)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }

        // 正式迭代
        while(true)
        {
            double cur_median;
            if(k & 1)
                cur_median = max_heap.top();
            else
                cur_median = ((double)max_heap.top() + min_heap.top()) * 0.5;
            result.push_back(cur_median);

            if(i >= (int)nums.size()) break;

            int out_num = nums[i - k];
            int in_num = nums[i];
            ++i;
            int balance = 0;

            // 处理 out_num 出窗
            balance += (out_num <= max_heap.top() ? -1 : 1);
            mapping[out_num]++;

            // 处理 in_num 入窗
            if(!max_heap.empty() && in_num <= max_heap.top())
            {
                balance++;
                max_heap.push(in_num);
            }
            else
            {
                balance--;
                min_heap.push(in_num);
            }

            // 重平衡
            if(balance < 0)
            {
                max_heap.push(min_heap.top());
                min_heap.pop();
                balance++;
            }
            if(balance > 0)
            {
                min_heap.push(max_heap.top());
                max_heap.pop();
                balance--;
            }

            // 删除无效的元素
            while(mapping[max_heap.top()])
            {
                mapping[max_heap.top()]--;
                max_heap.pop();
            }
            while(!min_heap.empty() && mapping[min_heap.top()])
            {
                mapping[min_heap.top()]--;
                min_heap.pop();
            }
        }
        return result;
    }
};

#include <functional>
#include <unordered_set>

class LabelOppositeHeap1 {
public:
    LabelOppositeHeap1()
    {
        pq_right = priority_queue<int, vector<int>, greater<int>>();
        pq_left = priority_queue<int>();
        left_cnt = 0, right_cnt = 0;
        label = unordered_map<int, int>();
    }

    double query()
    {
        clear_left_top();
        clear_right_top();
        double left = pq_left.top();
        if(left_cnt == right_cnt + 1)
            return left;
        double right = pq_right.top();
        return ((double)left + (double)right) / 2;
    }

    void insert(int x)
    {
        clear_left_top();
        clear_right_top();
        if(pq_left.empty() || x <= pq_left.top())
        {
            pq_left.push(x);
            ++left_cnt;
        }
        else
        {
            pq_right.push(x);
            ++right_cnt;
        }
        balance();
    }

    void label_delete(int x)
    {
        clear_left_top();
        clear_right_top();
        if(x <= pq_left.top())
            --left_cnt;
        else
            --right_cnt;
        ++label[x];
        balance();
    }

private:
    priority_queue<int, vector<int>, greater<int>> pq_right;
    priority_queue<int> pq_left;
    int left_cnt, right_cnt;
    unordered_map<int, int> label; // 哈希索引，用作删除标记

    void clear_right_top()
    {
        while(!pq_right.empty() && label.count(pq_right.top()))
        {
            --label[pq_right.top()];
            if(label[pq_right.top()] == 0)
                label.erase(pq_right.top());
            pq_right.pop();
        }
    }

    void clear_left_top()
    {
        while(!pq_left.empty() && label.count(pq_left.top()))
        {
            --label[pq_left.top()];
            if(label[pq_left.top()] == 0)
                label.erase(pq_left.top());
            pq_left.pop();
        }
    }

    void balance()
    {
        if(left_cnt > right_cnt + 1)
        {
            pq_right.push(pq_left.top());
            pq_left.pop();
            ++right_cnt;
            --left_cnt;
        }
        else if(left_cnt < right_cnt)
        {
            pq_left.push(pq_right.top());
            pq_right.pop();
            ++left_cnt;
            --right_cnt;
        }
    }
};

class Solution_3 {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        LabelOppositeHeap1 label_opposite_heap;
        for(int i = 0; i < k; ++i)
            label_opposite_heap.insert(nums[i]);
        int n = nums.size();
        vector<double> result(n - k + 1);
        for(int i = k; i < n; ++i)
        {
            result[i - k] = label_opposite_heap.query();
            label_opposite_heap.label_delete(nums[i - k]);
            label_opposite_heap.insert(nums[i]);
        }
        result[n - k] = label_opposite_heap.query();
        return result;
    }
};

//
class IndexMaxHeap
{
public:
    IndexMaxHeap()
    {
        data.assign(1, -1);
        _size = 0;
    }

    void build(const vector<int>& nums)
    {
        data.clear();
        mapping.clear();
        int n = nums.size();
        data.assign(n + 1, 0);
        data[0] = -1;
        for(int i = 0; i < n; ++i)
        {
            data[i + 1] = nums[i];
            mapping[nums[i]].insert(i + 1);
        }
        _size = n;
        for(int i = n; i >= 1; --i)
            push_down(i);
    }

    int top()
    {
        if(empty())
            return -1;
        return data[1];
    }

    int pop()
    {
        if(empty())
            return -1;
        int ans = data[1];
        _remove(1);
        return ans;
    }

    void push(int key)
    {
        if(_size + 1 >= (int)data.size())
            dilatation();
        ++_size;
        data[_size] = key;
        mapping[key].insert(_size);
        push_up(_size);
    }

    void remove(int key)
    {
        if(mapping.count(key) == 0)
            return;
        int i = *mapping[key].begin();
        _remove(i);
    }

    void change(int key, int new_key)
    {
        if(mapping.count(key) == 0)
            return;
        if(key == new_key)
            return;
        int i = *mapping[key].begin();
        mapping[key].erase(i);
        if(mapping[key].empty())
            mapping.erase(key);
        data[i] = new_key;
        mapping[new_key].insert(i);
        push_up(i);
        push_down(i);
    }

    int size()
    {
        return _size;
    }

    bool empty()
    {
        return _size == 0;
    }

private:
    vector<int> data; // keys
    int _size;
    unordered_map<int, unordered_set<int>> mapping; // key -> idxs

    void dilatation()
    {
        vector<int> tmp_data((_size + 1) * 2 + 1);
        tmp_data[0] = 1;
        for(int i = 1; i <= _size; ++i)
            tmp_data[i] = data[i];
        data.swap(tmp_data);
    }

    void _remove(int i)
    {
        if(i > _size)
            return;
        mapping[data[_size]].erase(_size);
        if(data[_size] != data[i])
        {
            mapping[data[_size]].insert(i);
            mapping[data[i]].erase(i);
            if(mapping[data[i]].empty())
                mapping.erase(data[i]);
        }
        data[i] = data[_size--];
        push_up(i);
        push_down(i);
    }

    void push_up(int i)
    {
        if(i > _size) return;
        while(i / 2 > 0 && data[i / 2] < data[i])
        {
            mapping[data[i]].erase(i);
            mapping[data[i]].insert(i / 2);
            mapping[data[i / 2]].erase(i / 2);
            mapping[data[i / 2]].insert(i);
            swap(data[i], data[i / 2]);
            i /= 2;
        }
    }

    void push_down(int i)
    {
        int ori = i, left = i * 2, right = i * 2 + 1;
        if(left <= _size && data[left] > data[ori])
            ori = left;
        if(right <= _size && data[right] > data[ori])
            ori = right;
        if(ori != i)
        {
            mapping[data[i]].erase(i);
            mapping[data[i]].insert(ori);
            mapping[data[ori]].erase(ori);
            mapping[data[ori]].insert(i);
            swap(data[i], data[ori]);
            push_down(ori);
        }
    }
};


class IndexMinHeap
{
public:
    IndexMinHeap()
    {
        data.assign(1, -1);
        _size = 0;
    }

    void build(const vector<int>& nums)
    {
        data.clear();
        mapping.clear();
        int n = nums.size();
        data.assign(n + 1, 0);
        data[0] = -1;
        for(int i = 0; i < n; ++i)
        {
            data[i + 1] = nums[i];
            mapping[nums[i]].insert(i + 1);
        }
        _size = n;
        for(int i = n; i >= 1; --i)
            push_down(i);
    }

    int top()
    {
        if(empty())
            return -1;
        return data[1];
    }

    int pop()
    {
        if(empty())
            return -1;
        int ans = data[1];
        _remove(1);
        return ans;
    }

    void push(int key)
    {
        if(_size + 1 >= (int)data.size())
            dilatation();
        ++_size;
        data[_size] = key;
        mapping[key].insert(_size);
        push_up(_size);
    }

    void remove(int key)
    {
        if(mapping.count(key) == 0)
            return;
        int i = *mapping[key].begin();
        _remove(i);
    }

    void change(int key, int new_key)
    {
        if(mapping.count(key) == 0)
            return;
        if(key == new_key)
            return;
        int i = *mapping[key].begin();
        mapping[key].erase(i);
        if(mapping[key].empty())
            mapping.erase(key);
        data[i] = new_key;
        mapping[new_key].insert(i);
        push_up(i);
        push_down(i);
    }

    int size()
    {
        return _size;
    }

    bool empty()
    {
        return _size == 0;
    }

private:
    vector<int> data; // keys
    int _size;
    unordered_map<int, unordered_set<int>> mapping; // key -> idxs

    void dilatation()
    {
        vector<int> tmp_data((_size + 1) * 2 + 1);
        tmp_data[0] = 1;
        for(int i = 1; i <= _size; ++i)
            tmp_data[i] = data[i];
        data.swap(tmp_data);
    }

    void _remove(int i)
    {
        if(i > _size)
            return;
        mapping[data[_size]].erase(_size);
        if(data[_size] != data[i])
        {
            mapping[data[_size]].insert(i);
            mapping[data[i]].erase(i);
            if(mapping[data[i]].empty())
                mapping.erase(data[i]);
        }
        data[i] = data[_size--];
        push_up(i);
        push_down(i);
    }

    void push_up(int i)
    {
        if(i > _size) return;
        while(i / 2 > 0 && data[i / 2] > data[i])
        {
            mapping[data[i]].erase(i);
            mapping[data[i]].insert(i / 2);
            mapping[data[i / 2]].erase(i / 2);
            mapping[data[i / 2]].insert(i);
            swap(data[i], data[i / 2]);
            i /= 2;
        }
    }

    void push_down(int i)
    {
        int ori = i, left = i * 2, right = i * 2 + 1;
        if(left <= _size && data[left] < data[ori])
            ori = left;
        if(right <= _size && data[right] < data[ori])
            ori = right;
        if(ori != i)
        {
            mapping[data[i]].erase(i);
            mapping[data[i]].insert(ori);
            mapping[data[ori]].erase(ori);
            mapping[data[ori]].insert(i);
            swap(data[i], data[ori]);
            push_down(ori);
        }
    }
};

class IndexOppositeHeap
{
public:
    IndexOppositeHeap(){}

    void insert(int x)
    {
        if(heap_left.empty() || x <= heap_left.top())
            heap_left.push(x);
        else
            heap_right.push(x);
        balance();
    }

    double query()
    {
        double left = heap_left.top();
        if(heap_left.size() == heap_right.size() + 1)
            return left;
        double right = heap_right.top();
        return ((double)left + (double)right) / 2;
    }

    void index_delete(int x)
    {
        if(!heap_left.empty() && x <= heap_left.top())
            heap_left.remove(x);
        else
            heap_right.remove(x);
        balance();
    }

private:
    IndexMaxHeap heap_left;
    IndexMinHeap heap_right;

    void balance()
    {
        if(heap_left.size() > heap_right.size() + 1)
        {
            heap_right.push(heap_left.top());
            heap_left.pop();
        }
        else if(heap_left.size() < heap_right.size())
        {
            heap_left.push(heap_right.top());
            heap_right.pop();
        }
    }
};

class Solution_4 {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        IndexOppositeHeap index_opposite_heap;
        for(int i = 0; i < k; ++i)
        {
            index_opposite_heap.insert(nums[i]);
        }
        int n = nums.size();
        vector<double> result(n - k + 1);
        for(int i = k; i < n; ++i)
        {
            result[i - k] = index_opposite_heap.query();
            index_opposite_heap.index_delete(nums[i - k]);
            index_opposite_heap.insert(nums[i]);
        }
        result[n - k] = index_opposite_heap.query();
        return result;
    }
};


//
class LabelMaxHeap
{
public:
    LabelMaxHeap()
    {
        data.assign(1, -1);
        _size = 0;
        _delete = 0;
    }

    void build(const vector<int>& nums)
    {
        data.clear();
        int n = nums.size();
        data.assign(n + 1, 0);
        data[0] = -1;
        for(int i = 0; i < n; ++i)
        {
            data[i + 1] = nums[i];
            ++label[data[i + 1]];
        }
        _size = n;
        for(int i = n; i >= 1; --i)
            push_down(i);
    }

    int top()
    {
        if(empty())
            return -1;
        while(label.count(data[1]) == 0)
        {
            data[1] = data[_size--];
            --_delete;
            push_down(1);
        }
        return data[1];
    }

    int pop()
    {
        if(empty())
            return -1;
        int ans = top();
        --label[ans];
        if(label[ans] == 0)
            label.erase(ans);
        data[1] = data[_size--];
        push_down(1);
        return ans;
    }

    void push(int key)
    {
        if(_size + 1 >= (int)data.size())
            dilatation();
        ++label[key];
        data[++_size] = key;
        push_up(_size);
    }

    void remove(int key)
    {
        if(label.count(key) == 0)
            return;
        --label[key];
        if(label[key] == 0)
            label.erase(key);
        ++_delete;
    }

    int size()
    {
        return _size - _delete;
    }

    bool empty()
    {
        return size() == 0;
    }

private:
    vector<int> data; // keys
    int _size;
    int _delete;
    unordered_map<int, int> label; // key -> cnts

    void dilatation()
    {
        vector<int> tmp_data((_size + 1) * 2 + 1);
        tmp_data[0] = 1;
        for(int i = 1; i <= _size; ++i)
            tmp_data[i] = data[i];
        data.swap(tmp_data);
    }

    void push_up(int i)
    {
        if(i > _size) return;
        while(i / 2 > 0 && data[i / 2] < data[i])
        {
            swap(data[i], data[i / 2]);
            i /= 2;
        }
    }

    void push_down(int i)
    {
        int ori = i, left = i * 2, right = i * 2 + 1;
        if(left <= _size && data[left] > data[ori])
            ori = left;
        if(right <= _size && data[right] > data[ori])
            ori = right;
        if(ori != i)
        {
            swap(data[i], data[ori]);
            push_down(ori);
        }
    }
};

class LabelMinHeap
{
public:
    LabelMinHeap()
    {
        data.assign(1, -1);
        _size = 0;
        _delete = 0;
    }

    void build(const vector<int>& nums)
    {
        data.clear();
        int n = nums.size();
        data.assign(n + 1, 0);
        data[0] = -1;
        for(int i = 0; i < n; ++i)
        {
            data[i + 1] = nums[i];
            ++label[data[i + 1]];
        }
        _size = n;
        for(int i = n; i >= 1; --i)
            push_down(i);
    }

    int top()
    {
        if(empty())
            return -1;
        while(label.count(data[1]) == 0)
        {
            data[1] = data[_size--];
            --_delete;
            push_down(1);
        }
        return data[1];
    }

    int pop()
    {
        if(empty())
            return -1;
        int ans = top();
        --label[ans];
        if(label[ans] == 0)
            label.erase(ans);
        data[1] = data[_size--];
        push_down(1);
        return ans;
    }

    void push(int key)
    {
        if(_size + 1 >= (int)data.size())
            dilatation();
        ++label[key];
        data[++_size] = key;
        push_up(_size);
    }

    void remove(int key)
    {
        if(label.count(key) == 0)
            return;
        --label[key];
        if(label[key] == 0)
            label.erase(key);
        ++_delete;
    }

    int size()
    {
        return _size - _delete;
    }

    bool empty()
    {
        return size() == 0;
    }

private:
    vector<int> data; // keys
    int _size;
    int _delete;
    unordered_map<int, int> label; // key -> cnts

    void dilatation()
    {
        vector<int> tmp_data((_size + 1) * 2 + 1);
        tmp_data[0] = 1;
        for(int i = 1; i <= _size; ++i)
            tmp_data[i] = data[i];
        data.swap(tmp_data);
    }

    void push_up(int i)
    {
        if(i > _size) return;
        while(i / 2 > 0 && data[i / 2] > data[i])
        {
            swap(data[i], data[i / 2]);
            i /= 2;
        }
    }

    void push_down(int i)
    {
        int ori = i, left = i * 2, right = i * 2 + 1;
        if(left <= _size && data[left] < data[ori])
            ori = left;
        if(right <= _size && data[right] < data[ori])
            ori = right;
        if(ori != i)
        {
            swap(data[i], data[ori]);
            push_down(ori);
        }
    }
};

class LabelOppositeHeap
{
public:
    LabelOppositeHeap(){}

    void insert(int x)
    {
        if(heap_left.empty() || x <= heap_left.top())
            heap_left.push(x);
        else
            heap_right.push(x);
        balance();
    }

    double query()
    {
        double left = heap_left.top();
        if(heap_left.size() == heap_right.size() + 1)
            return left;
        double right = heap_right.top();
        return ((double)left + (double)right) / 2;
    }

    void index_delete(int x)
    {
        if(!heap_left.empty() && x <= heap_left.top())
            heap_left.remove(x);
        else
            heap_right.remove(x);
        balance();
    }

private:
    LabelMaxHeap heap_left;
    LabelMinHeap heap_right;

    void balance()
    {
        if(heap_left.size() > heap_right.size() + 1)
        {
            heap_right.push(heap_left.top());
            heap_left.pop();
        }
        else if(heap_left.size() < heap_right.size())
        {
            heap_left.push(heap_right.top());
            heap_right.pop();
        }
    }
};

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        LabelOppositeHeap label_opposite_heap;
        for(int i = 0; i < k; ++i)
        {
            label_opposite_heap.insert(nums[i]);
        }
        int n = nums.size();
        vector<double> result(n - k + 1);
        for(int i = k; i < n; ++i)
        {
            result[i - k] = label_opposite_heap.query();
            label_opposite_heap.index_delete(nums[i - k]);
            label_opposite_heap.insert(nums[i]);
        }
        result[n - k] = label_opposite_heap.query();
        return result;
    }
};


