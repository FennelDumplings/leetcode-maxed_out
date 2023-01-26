// prob1562: Find Latest Group of Size M

/*
 * https://leetcode-cn.com/problems/find-latest-group-of-size-m/
 */

#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_set>

using namespace std;

class Solution_10 {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        string str(n, '0');
        map<int, int> ranges;
        for(int i = 0; i < n; ++i)
        {
            str[arr[i] - 1] = '1';
        }
        int left = 0;
        int ans = n;
        while(left < n)
        {
            while(left < n && str[left] == '0')
                ++left;
            if(left == n)
                break;
            int right = left + 1;
            while(right < n && str[right] == '1')
                ++right;
            if(right - left == m)
                return ans;
            ranges[left] = right - 1;
            left = right;
        }
        for(int i = n - 1; i >= 0; --i)
        {
            --ans;
            int mid = arr[i] - 1;
            auto it = ranges.upper_bound(mid);
            if(it != ranges.begin())
                --it;
            int l = it -> first;
            int r = it -> second;
            ranges.erase(it);
            if(l < mid)
            {
                int len_left = mid - l;
                if(len_left == m)
                    return ans;
                ranges[l] = mid - 1;
            }
            if(mid < r)
            {
                int len_right = r - mid;
                if(len_right == m)
                    return ans;
                ranges[mid + 1] = r;
            }
        }
        return -1;
    }
};

class Solution_2 {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        vector<Range> range(n + 1);
        int cnt_m = 0;
        int ans = -1;
        for(int i = 0; i < n; ++i)
        {
            int val = arr[i];
            int len_val;
            if((val < n && range[val + 1].l != -1) && (val > 1 && range[val - 1].l != -1))
            {
                range[range[val - 1].l].r = range[val + 1].r;
                range[range[val + 1].r].l = range[val - 1].l;
                len_val = range[val + 1].r - range[val - 1].l + 1;
                if(range[val + 1].r - val == m)
                    --cnt_m;
                if(val - range[val - 1].l == m)
                    --cnt_m;
            }
            else if(val < n && range[val + 1].l != -1)
            {
                range[range[val + 1].r].l = val;
                range[val].r = range[val + 1].r;
                range[val].l = val;
                len_val = range[val + 1].r - val + 1;
                if(range[val + 1].r - val == m)
                    --cnt_m;
            }
            else if(val > 1 && range[val - 1].l != -1)
            {
                range[range[val - 1].l].r = val;
                range[val].l = range[val - 1].l;
                range[val].r = val;
                len_val = val - range[val - 1].l + 1;
                if(val - range[val - 1].l == m)
                    --cnt_m;
            }
            else
            {
                range[val].l = val;
                range[val].r = val;
                len_val = 1;
            }
            if(len_val == m)
                ++cnt_m;
            if(cnt_m > 0)
                ans = i + 1;
        }
        return ans;
    }

private:
    struct Range
    {
        int l, r;
        Range(int l, int r):l(l),r(r){}
        Range():l(-1),r(-1){}
    };
};

//

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        // 维护 [1..n]
        _father.assign(n + 1, 0);
        _rank.assign(n + 1, 0);
        _weight.assign(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            _father[i] = i;
    }

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y)
            return;

        if(_rank[x] < _rank[y])
        {
            _father[x] = y;
            _weight[y] += _weight[x];
        }
        else
        {
            _father[y] = x;
            _weight[x] += _weight[y];
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

    void set(int x)
    {
        _weight[x] = 1;
    }

    int get(int x)
    {
        return _weight[_find(x)];
    }

private:
    vector<int> _father;
    vector<int> _rank;
    vector<int> _weight;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution_3 {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        UnionFindSet unionfindset(n);
        int ans = -1;
        int cnt_m = 0;
        for(int i = 0; i < n; ++i)
        {
            int val = arr[i];
            unionfindset.set(val);
            if(val > 1)
            {
                int len_left = unionfindset.get(val - 1);
                if(len_left > 0)
                {
                    if(len_left == m)
                        --cnt_m;
                    unionfindset.merge(val, val - 1);
                }
            }
            if(val < n)
            {
                int len_right = unionfindset.get(val + 1);
                if(len_right > 0)
                {
                    if(len_right == m)
                        --cnt_m;
                    unionfindset.merge(val, val + 1);
                }
            }
            int val_len = unionfindset.get(val);
            if(val_len == m)
                ++cnt_m;
            if(cnt_m > 0)
                ans = i + 1;
        }
        return ans;
    }
};


class Solution_4 {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if(n == m) return n;
        // m < n
        map<int, int> ranges;
        ranges[1] = n;
        for(int i = n - 1; i >= 0; --i)
        {
            int val = arr[i];
            auto it = prev(ranges.upper_bound(val));
            int l = it -> first;
            int r = it -> second;
            ranges.erase(it);
            if(val - 1 >= l)
            {
                if(val - l == m)
                    return i;
                ranges[l] = val - 1;
            }
            if(val + 1 <= r)
            {
                if(r - val == m)
                    return i;
                ranges[val + 1] = r;
            }
        }
        return -1;
    }
};

class Solution_5 {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        int ans = solve(arr, n - 1, 1, n, m);
        return ans == -1 ? -1 : n - ans;
    }

private:
    int solve(const vector<int>& arr, int idx, int l, int r, const int m)
    {
        // 返回 s[l..r] 上首次出现长 m 全 1 串的时间
        // 子问题直接可解的情况
        // [l, r] 长度刚好为 m，返回 0
        if(r - l + 1 == m)
            return 0;
        if(l > r)
            return -1;
        if(r - l + 1 < m)
            return -1;
        if(arr[idx] < l || arr[idx] > r)
        {
            int ans = solve(arr, idx - 1, l, r, m);
            return ans == -1 ? -1 : 1 + ans;
        }
        // 子问题分割点 s[l, arr[idx] - 1], s[arr[idx]], s[arr[idx] + 1, r]
        int left = solve(arr, idx - 1, l, arr[idx] - 1, m);
        int right = solve(arr, idx - 1, arr[idx] + 1, r, m);
        if(right == -1 && left == -1)
            return -1;
        else if(left == -1)
            return right + 1;
        else if(right == -1)
            return left + 1;
        else
            return min(left, right) + 1;
    }
};

class Solution_6 {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        vector<int> lens(n + 2);
        int cnt_m = 0;
        int ans = -1;
        for(int i = 0; i < n; ++i)
        {
            int val = arr[i];
            if(lens[val - 1] == m)
                --cnt_m;
            if(lens[val + 1] == m)
                --cnt_m;
            lens[val] = lens[val - 1] + lens[val + 1] + 1;
            if(lens[val] == m)
                ++cnt_m;
            if(cnt_m > 0)
                ans = i + 1;
            lens[val + lens[val + 1]] = lens[val];
            lens[val - lens[val - 1]] = lens[val];
        }
        return ans;
    }
};

#include <deque>

class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if(n == m) return n;
        // vec[0, 1, ..., n, n + 1]
        vector<int> vec(n + 2, n + 1);
        for(int i = 0; i < n; ++i)
            vec[arr[i]] = i + 1;
        deque<int> deq;
        int ans = -1;
        // 将 deq 中预处理好 vec[1..m-1] 这个长 m-1 的窗口
        for(int i = 1; i < m; ++i)
        {
            while(!deq.empty() && vec[deq.back()] <= vec[i])
                deq.pop_back();
            deq.push_back(i);
        }
        for(int i = m; i < n + 1; ++i)
        {
            while(!deq.empty() && vec[deq.back()] <= vec[i])
                deq.pop_back();
            deq.push_back(i);
            // 此时 deq 中是 [i-m+1..i] 的信息
            int min_neighbor = min(vec[i + 1], vec[i - m]);
            if(vec[deq.front()] < min_neighbor)
                ans = max(ans, min_neighbor - 1);
            // 迭代下一个 i 之前，将窗口调整为 [i-m+2, i]
            if(deq.front() == i - m + 1)
                deq.pop_front();
        }
        return ans;
    }
};
