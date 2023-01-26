// 面51: 数组中的逆序对

/*
 * 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
 */

/*
 * 示例 1:
 * 输入: [7,5,6,4]
 * 输出: 5
 */

#include <vector>
#include <algorithm>

using namespace std;

// 在归并排序的归并阶段求逆序对个数
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 0;
        return _mergesort(nums, 0, n - 1);
    }

private:
    int _mergesort(vector<int>& nums, int left, int right)
    {
        int mid = left + (right - left) / 2;
        int res = 0;
        if(left == right) return 0;
        res += _mergesort(nums, left, mid);
        res += _mergesort(nums, mid + 1, right);
        res += _merge(nums, left, mid + 1, right);
        return res;
    }

    int _merge(vector<int>& nums, int left, int mid, int right)
    {
        int i = left, j = mid, k = 0;
        int res = 0;
        vector<int> tmp(right - left + 1, 0);
        while(i < mid && j <= right)
        {
            if(nums[i] > nums[j])
            {
                res += mid - i;
                tmp[k] = nums[j];
                ++k;
                ++j;
            }
            else
            {
                tmp[k] = nums[i];
                ++k;
                ++i;
            }
        }
        while(i < mid) tmp[k++] = nums[i++];
        while(j <= right) tmp[k++] = nums[j++];
        for(i = left, k = 0; i <= right; ++i, ++k)
            nums[i] = tmp[k];
        return res;
    }
};

// 权值线段树
struct STNode
{
    int start, end;
    int cnt;
    STNode *left, *right;
    STNode(int s, int e, int c, STNode* l=nullptr, STNode* r=nullptr)
        :start(s),end(e),cnt(c),left(l),right(r){}
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

    void build(int start, int end)
    {
        if(start <= end)
            root = _build(start, end);
    }

    void add(int index)
    {
        _add(root, index);
    }

    int query(int i, int j)
    {
        if(i > j) return 0;
        return _query(root, i, j);
    }


private:
    STNode *root;

    STNode* _build(int start, int end)
    {
        if(start == end)
            return new STNode(start, end, 0);
        int mid = start + (end - start) / 2;
        STNode *left = _build(start, mid);
        STNode *right = _build(mid + 1, end);
        return new STNode(start, end, 0, left, right);
    }

    void _add(STNode* root,int index)
    {
        if(!root) return;
        if(root -> start == root -> end && root -> start == index)
        {
            ++(root -> cnt);
            return;
        }
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(index > mid)
            _add(root -> right, index);
        else
            _add(root -> left, index);
        ++(root -> cnt);
    }

    int _query(STNode* root, int i, int j)
    {
        if(!root) return 0;
        if(root -> start == i && root -> end == j)
            return root -> cnt;
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(j <= mid)
            return _query(root -> left, i, j);
        else if(i > mid)
            return _query(root -> right, i, j);
        else
            return _query(root -> left, i, mid) + _query(root -> right, mid + 1, j);
    }
};

class Solution_2 {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return 0;
        vector<int> x; // 离散化后的值
        for(int i: nums)
            x.push_back(i);
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());

        int m = x.size();
        SegmentTree segmenttree;
        segmenttree.build(0, m - 1);
        segmenttree.add(_find(nums[0], x));
        int result = 0;
        for(int i = 1; i < n; ++i)
        {
            int order = _find(nums[i], x);
            if(order <= m - 1)
                result += segmenttree.query(order + 1, m - 1);
            segmenttree.add(order);
        }
        return result;
    }

private:
    int _find(int v, const vector<int>& x)
    {
        // 返回 v 离散化后在 x 中的索引 从 0 开始
        // 若为从 1 开始，再加上 1
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};
