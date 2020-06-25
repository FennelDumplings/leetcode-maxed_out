// prob999: Falling Squares

/*
 * https://leetcode-cn.com/problems/falling-squares/
 */

/*
 * Note:
 * 1 <= positions.length <= 1000.
 * 1 <= positions[i][0] <= 10^8.
 * 1 <= positions[i][1] <= 10^6.
 */

#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

class Ranges
{
public:
    Ranges()
    {
        ranges = map<int, PII>();
        max_h = 0;
    }

    int update(int start, int end, int len)
    {
        // [start, end) 范围的 h 最大值, 返回 h
        IT l, r;
        get_overlap(start, end, l, r);
        // [l, r) 为有重叠的区间
        if(l == r) // [start, end) 范围无已有区间
        {
            ranges.insert(PIP(start, PII(end, len)));
            max_h = max(max_h, len);
            return max_h;
        }
        auto last = r;
        --last;

        bool has_left = false, has_right = false;
        int left_l = l -> first;
        int left_r = start;
        int left_h = (l -> second).second;
        int right_l = end;
        int right_r = (last -> second).first;
        int right_h = (last -> second).second;
        if(left_l < left_r)
            has_left = true;
        if(right_l < right_r)
            has_right = true;

        auto iter = l;
        int h = (iter -> second).second;
        ++iter;
        while(iter != r)
        {
            h = max(h, (iter -> second).second);
            ++iter;
        }

        ranges.erase(l, r);
        if(has_left)
            ranges.insert(PIP(left_l, PII(left_r, left_h)));
        if(has_right)
            ranges.insert(PIP(right_l, PII(right_r, right_h)));
        int new_h = h + len;
        ranges.insert(PIP(start, PII(end, new_h)));
        max_h = max(max_h, new_h);
        return max_h;
    }

private:
    using PII = pair<int, int>;
    using PIP = pair<int, PII>;
    using IT = map<int, PII>::iterator;
    map<int, PII> ranges; // left -> (right, h)
    int max_h;

    void get_overlap(int left, int right, IT& l, IT& r)
    {
        l = ranges.upper_bound(left);
        r = ranges.lower_bound(right);
        if(l != ranges.begin())
        {
            --l;
            if((l -> second).first <= left)
                ++l;
        }
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> result(n, -1);
        Ranges ranges;
        for(int i = 0; i < n; ++i)
        {

            int left = positions[i][0];
            int len = positions[i][1];
            int right = left + len; // right 是开区间
            result[i] = ranges.update(left, right, len);
        }
        return result;
    }
};

// RMQ 数组写法
class SeqSegmentTree
{
public:
    SeqSegmentTree()
    {
        st_vec = vector<int>();
        lazy = vector<int>();
        n = -1;
    }

    void build(const vector<int>& nums)
    {
        if(nums.empty()) return;
        n = nums.size();
        st_vec.resize(n * 4);
        lazy.resize(n * 4);
        _build(1, 0, n - 1, nums);
    }

    void range_update(int i, int j, int v)
    {
        // [i, j] 范围内改为 v
        _range_update(1, 0, n - 1, i, j, v);
    }

    int range_query(int i, int j)
    {
        return _range_query(1, 0, n - 1, i, j);
    }

private:
    int _range_query(int node, int nodeLeft, int nodeRight, int start, int end)
    {
        if(nodeLeft == start && nodeRight == end)
            return st_vec[node];
        int nodeMid = (nodeLeft + nodeRight) / 2;
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        push_down(node);
        if(end <= nodeMid)
            return _range_query(left_son, nodeLeft, nodeMid, start, end);
        else if(nodeMid < start)
            return _range_query(right_son, nodeMid + 1, nodeRight, start, end);
        else
        {
            return max(_range_query(left_son, nodeLeft, nodeMid, start, nodeMid),
                    _range_query(right_son, nodeMid + 1, nodeRight, nodeMid + 1, end));
        }
    }

    void _range_update(int node, int nodeLeft, int nodeRight, int start, int end, int v)
    {
        if(nodeLeft == start && nodeRight == end)
        {
            lazy[node] = v;
            st_vec[node] = v;
            return;
        }
        if(nodeLeft == nodeRight) return;
        int nodeMid = (nodeLeft + nodeRight) / 2;
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        push_down(node);
        if(end <= nodeMid)
            _range_update(left_son, nodeLeft, nodeMid, start, end, v);
        else if(nodeMid < start)
            _range_update(right_son, nodeMid + 1, nodeRight, start, end, v);
        else
        {
            _range_update(left_son, nodeLeft, nodeMid, start, nodeMid, v);
            _range_update(right_son, nodeMid + 1, nodeRight, nodeMid + 1, end, v);
        }
        push_up(node);
    }

    // 懒标记下传
    void push_down(int node)
    {
        if(lazy[node])
        {
            // 节点 node 有 lazy 标记
            int left_son = node * 2;
            int right_son = node * 2 + 1;
            // 如果 lazy = v 的含义是区间内的值都加 v，则是如下写法
            lazy[left_son] = lazy[node]; // 向左子节点传递
            lazy[right_son] = lazy[node]; // 向右子节点传递
            st_vec[left_son] = lazy[node];
            st_vec[right_son] = lazy[node];
            // 如果 lazy = v 的含义是区间内的值都改为 v，则将以上的 += 改为 =
            lazy[node] = 0;
        }
    }

    // 查询结果上传
    void push_up(int node)
    {
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        st_vec[node] = max(st_vec[left_son], st_vec[right_son]);
    }

    void _build(int node, int nodeLeft, int nodeRight, const vector<int>& nums)
    {
        if(nodeLeft == nodeRight)
        {
            st_vec[node] = nums[nodeLeft];
            return;
        }
        int nodeMid = (nodeLeft + nodeRight) / 2;
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        _build(left_son, nodeLeft, nodeMid, nums);
        _build(right_son, nodeMid + 1, nodeRight, nums);
        st_vec[node] = max(st_vec[left_son], st_vec[right_son]);
    }

    vector<int> st_vec; // 节点值表示区间最大值
    vector<int> lazy;
    int n;
};

class Solution_2 {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // 离散化
        vector<int> x;
        for(const vector<int>& pos: positions)
        {
            x.push_back(pos[0]);
            x.push_back(pos[0] + pos[1] - 1);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());

        int n = x.size();
        SeqSegmentTree seqsttree;
        vector<int> arr(n);
        seqsttree.build(arr);
        vector<int> result;
        for(const vector<int>& pos: positions)
        {
            int start = _find(pos[0], x);
            int end = _find(pos[0] + pos[1] - 1, x);
            int v = pos[1];
            int maxx = seqsttree.range_query(start, end);
            seqsttree.range_update(start, end, maxx + v);
            result.push_back(seqsttree.range_query(0, n - 1));
        }
        return result;
    }

private:
    int _find(int v, const vector<int>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};

// RMQ 链式写法
struct STNode
{
    int nodeLeft, nodeRight;
    int maxx;
    STNode *left, *right;
    int lazy;
    STNode(int l, int r, int x, STNode* left=nullptr, STNode* right=nullptr)
        :nodeLeft(l),nodeRight(r),maxx(x),left(left),right(right),lazy(0){}
    ~STNode()
    {
        if(left)
        {
            delete left;
            left = nullptr;
        }
        if(right)
        {
            delete right;
            right = nullptr;
        }
    }
};

class SegmentTree
{
public:
    SegmentTree()
    {
        root = nullptr;
    }

    ~SegmentTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void range_update(int i, int j, int v)
    {
        // cout << "range_update(" << i << "," << j << "," << v << ")" << endl;
        _range_update(root, i, j, v);
    }

    int range_query(int i, int j)
    {
        // cout << "range_query(" << i << "," << j << ")" << endl;
        return _range_query(root, i, j);
    }

    void build(const vector<int>&arr)
    {
        if(arr.empty()) return;
        int n = arr.size();
        root = _build(0, n - 1, arr);
    }

    void traverse()
    {
        cout << "==================" << endl;
        _traverse(root);
        cout << "==================" << endl;
    }

private:
    STNode *root;

    void _traverse(STNode* node)
    {
        // cout << "Range: [";
        // cout << node -> nodeLeft << " , " << node -> nodeRight << "]" << endl;
        // cout << "Max: " << node -> maxx << endl;
        if(node -> nodeLeft != node -> nodeRight)
        {
            _traverse(node -> left);
            _traverse(node -> right);
        }
    }

    // 懒标记下传
    void push_down(STNode* node)
    {
        if(node -> lazy)
        {
            node -> left -> lazy = node -> lazy;
            node -> right -> lazy = node -> lazy;
            node -> left -> maxx = node -> lazy;
            node -> right -> maxx = node -> lazy;
            node -> lazy = 0;
        }
    }

    // 查询结果上传
    void push_up(STNode* node)
    {
        node -> maxx = max(node -> left -> maxx, node -> right -> maxx);
    }

    int _range_query(STNode* node, int start, int end)
    {
        int nodeLeft = node -> nodeLeft;
        int nodeRight = node -> nodeRight;
        if(nodeLeft == start && nodeRight == end)
            return node -> maxx;
        int nodeMid = (nodeLeft + nodeRight) / 2;
        // 要根据子树结果计算当前节点结果时，懒标记下传
        push_down(node);
        if(end <= nodeMid)
            return _range_query(node -> left, start, end);
        else if(nodeMid < start)
            return _range_query(node -> right, start, end);
        else
        {
            return max(_range_query(node -> left, start, nodeMid),
                    _range_query(node -> right, nodeMid + 1, end));
        }
    }

    void _range_update(STNode* node, int start, int end, int v)
    {
        int nodeLeft = node -> nodeLeft;
        int nodeRight = node -> nodeRight;
        // cout << "_range_update(" << nodeLeft << "," << nodeRight << "," << v << "," << start << "," << end << ")" << endl;
        if(nodeLeft == start && nodeRight == end)
        {
            node -> lazy = v;
            node -> maxx = v;
            return;
        }
        int nodeMid = (nodeLeft + nodeRight) / 2;
        if(nodeLeft == nodeRight) return;
        // cout << nodeLeft << " " << nodeRight << endl;
        // 下传懒标记
        push_down(node);
        if(end <= nodeMid)
        {
            // cout << "end <= nodeMid" << endl;
            _range_update(node -> left, start, end, v);
        }
        else if(nodeMid < start)
        {
            // cout << "nodeMid < start" << endl;
            _range_update(node -> right, start, end, v);
        }
        else
        {
            // cout << "start < nodeMid < end " << endl;
            _range_update(node -> left, start, nodeMid, v);
            _range_update(node -> right, nodeMid + 1, end, v);
        }
        push_up(node);
    }

    STNode* _build(int nodeLeft, int nodeRight, const vector<int>& arr)
    {
        if(nodeLeft == nodeRight)
            return new STNode(nodeLeft, nodeRight, arr[nodeLeft]);
        int nodeMid = (nodeLeft + nodeRight) / 2;
        STNode *left_son = _build(nodeLeft, nodeMid, arr);
        STNode *right_son = _build(nodeMid + 1, nodeRight, arr);
        int maxx = max(left_son -> maxx, right_son -> maxx);
        return new STNode(nodeLeft, nodeRight, maxx, left_son, right_son);
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // 离散化
        vector<int> x;
        for(const vector<int>& pos: positions)
        {
            x.push_back(pos[0]);
            x.push_back(pos[0] + pos[1] - 1);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());

        int n = x.size();
        SegmentTree sttree;
        vector<int> arr(n);
        sttree.build(arr);
        vector<int> result;
        // sttree.traverse();
        for(const vector<int>& pos: positions)
        {
            int start = _find(pos[0], x);
            int end = _find(pos[0] + pos[1] - 1, x);
            int v = pos[1];
            int maxx = sttree.range_query(start, end);
            sttree.range_update(start, end, maxx + v);
            result.push_back(sttree.range_query(0, n - 1));
        }
        return result;
    }

private:
    int _find(int v, const vector<int>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};

// 分块 RMQ
class Block
{
public:
    Block(){}

    void build(const vector<int>& arr)
    {
        nums = arr;
        n = nums.size();
        block_size = floor(sqrt(n)); // 8 -> 2, 9 -> 3, 10 -> 3, 11 -> 3, ..., 15 -> 3, 16 -> 4
        bn = n / block_size + 1; // 最后一个桶的元素个数可能为 [0, block_size - 1]
        lazy = vector<int>(bn, 0);
        maxx = vector<int>(bn, 0);
        has_lazy = vector<bool>(bn, false);
        for(int i = 0; i < n; ++i)
        {
            int bucket_id = i / block_size;
            maxx[bucket_id] = max(maxx[bucket_id], nums[i]);
        }
    }

    void point_update(int idx, int x)
    {
        // 先将对应块的标记 `lazy[i]` 下传，再暴力更新被修改块的状态。时间复杂度 O(\sqrt(N))
        int bucket_id = idx / block_size;
        if(has_lazy[bucket_id])
        {
            for(int i = bucket_id * block_size; i < min((bucket_id + 1) * block_size, n); ++i)
                nums[i] = lazy[bucket_id];
            has_lazy[bucket_id] = false;
        }
        nums[idx] = x;
        maxx[bucket_id] = max(maxx[bucket_id], x);
    }

    void range_update(int l, int r, int x)
    {
        int bucket_l = l / block_size, bucket_r = r / block_size;
        // 左半桶
        if(has_lazy[bucket_l])
        {
            for(int i = bucket_l * block_size; i < min((bucket_l + 1) * block_size, n); ++i)
                nums[i] = lazy[bucket_l];
            has_lazy[bucket_l] = false;
        }
        for(int i = l; i <= min((bucket_l + 1) * block_size - 1, r); ++i)
            nums[i] = x;
        maxx[bucket_l] = max(maxx[bucket_l], x);
        // 右半桶
        if(bucket_l != bucket_r)
        {
            if(has_lazy[bucket_r])
            {
                for(int i = bucket_r * block_size; i < min((bucket_r + 1) * block_size, n); ++i)
                    nums[i] = lazy[bucket_r];
                has_lazy[bucket_r] = false;
            }
            for(int i = bucket_r * block_size; i <= r; ++i)
                nums[i] = x;
            maxx[bucket_r] = max(maxx[bucket_r], x);
        }
        // 中间的桶
        for(int bucket_id = bucket_l + 1; bucket_id < bucket_r; ++bucket_id)
        {
            lazy[bucket_id] = x;
            has_lazy[bucket_id] = true;
            maxx[bucket_id] = x;
        }
    }

    int range_query(int l, int r)
    {
        // 对于中间跨过的整块，直接利用块保存的信息统计答案，两端剩余部分任然可以暴力扫描统计。
        int bucket_l = l / block_size, bucket_r = r / block_size;
        int result = nums[l];

        // 左半桶
        if(has_lazy[bucket_l])
            result = maxx[bucket_l];
        else
            for(int i = l; i <= min((bucket_l + 1) * block_size - 1, r); ++i)
                result = max(result, nums[i]);
        // 右半桶
        if(bucket_l != bucket_r)
        {
            if(has_lazy[bucket_r])
                result = max(result, maxx[bucket_r]);
            else
                for(int i = bucket_r * block_size; i <= r; ++i)
                    result = max(result, nums[i]);
        }
        // 中间的桶
        for(int bucket_id = bucket_l + 1; bucket_id < bucket_r; ++bucket_id)
            result = max(result, maxx[bucket_id]);
        return result;
    }

    vector<int> nums;
    vector<int> maxx;
    vector<int> lazy;
    vector<bool> has_lazy;
    int block_size, bn, n;
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // 离散化
        vector<int> x;
        for(const vector<int>& pos: positions)
        {
            x.push_back(pos[0]);
            x.push_back(pos[0] + pos[1] - 1);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());

        int n = x.size();
        Block block;
        vector<int> arr(n);
        block.build(arr);
        vector<int> result;
        // sttree.traverse();
        for(const vector<int>& pos: positions)
        {
            int start = _find(pos[0], x);
            int end = _find(pos[0] + pos[1] - 1, x);
            int v = pos[1];
            int maxx = block.range_query(start, end);
            block.range_update(start, end, maxx + v);
            result.push_back(block.range_query(0, n - 1));
        }
        return result;
    }

private:
    int _find(int v, const vector<int>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};
