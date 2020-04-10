// prob315: Count of Smaller Numbers After Self

/*
 * You are given an integer array nums and you have to return a new counts array. The counts
 * array has the property where counts[i] is the number of smaller elements to the right of nums[i].
 */

/*
 * Example:
 * Input: [5,2,6,1]
 * Output: [2,1,1,0]
 * Explanation:
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 */

#include <vector>
#include <algorithm>

using namespace std;

// 线段树 / 树状数组
struct STNode
{
    int start, end;
    int sum;
    STNode *left, *right;
    STNode(int s, int e, int v, STNode* l=nullptr, STNode* r=nullptr)
        :start(s), end(e), sum(v), left(l), right(r) {}
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
        if(i > j)
            return 0;
        return _query(root, i, j);
    }

private:
    STNode *root;

    int _query(STNode* root, int i, int j)
    {
        if(!root) return 0;
        if(root -> start == i && root -> end == j)
            return root -> sum;
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(j <= mid)
            return _query(root -> left, i, j);
        if(mid < i)
            return _query(root -> right, i, j);
        return _query(root -> left, i, mid) + _query(root -> right, mid + 1, j);
    }

    void _add(STNode* root, int index)
    {
        if(!root) return;
        if(root -> start == index && root -> end == index)
        {
            ++(root -> sum);
            return;
        }
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(mid >= index)
            _add(root -> left, index);
        else
            _add(root -> right, index);
        ++(root -> sum);
    }

    STNode* _build(int start, int end)
    {
        if(start == end)
            return new STNode(start, end, 0);
        int mid = start + (end - start) / 2;
        STNode *left = _build(start, mid);
        STNode *right = _build(mid + 1, end);
        return new STNode(start, end, 0, left, right);
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        vector<int> x(nums.begin(), nums.end()); // 离散化后的值
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        int m = x.size();

        SegmentTree segmenttree;
        segmenttree.build(0, m - 1);
        vector<int> result(n);
        result[n - 1] = 0;
        segmenttree.add(_find(nums[n - 1], x));
        for(int i = n - 2; i >= 0; --i)
        {
            result[i] = segmenttree.query(0, _find(nums[i], x) - 1);
            cout << _find(nums[i], x) - 1 << endl;
            segmenttree.add(_find(nums[i], x));
        }
        return result;
    }

private:
    int _find(int v, const vector<int>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};

// CDQ 分治
class Solution_2 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n == 1) return vector<int>({0});
        vector<int> indexes(n, 0);
        for(int i = 1; i < n; ++i)
            indexes[i] = i;
        vector<int> result(n, 0);
        _mergesort(nums, indexes, result, 0, n - 1);
        return result;
    }

private:
    void _mergesort(const vector<int>& nums, vector<int>& indexes, vector<int>& result, int left, int right)
    {
        if(left == right) return;
        int mid = left + (right - left) / 2;
        _mergesort(nums, indexes, result, left, mid);
        _mergesort(nums, indexes, result, mid + 1, right);
        _merge(nums, indexes, result, left, mid, right);
    }

    void _merge(const vector<int>& nums, vector<int>& indexes, vector<int>& result, int left, int mid, int right)
    {
        vector<int> tmp(right - left + 1, 0);
        int i = left, j = mid + 1, k = 0;
        while(i <= mid && j <= right)
        {
            int pi = nums[indexes[i]], qj = nums[indexes[j]];
            if(pi <= qj)
            {
                result[indexes[i]] += (j - mid - 1);
                tmp[k++] = indexes[i++];
            }
            else
                tmp[k++] = indexes[j++];
        }
        while(i <= mid)
        {
            result[indexes[i]] += (j - mid - 1);
            tmp[k++] = indexes[i++];
        }
        while(j <= right) tmp[k++] = indexes[j++];
        for(i = left, k = 0; i <= right; ++i, ++k)
            indexes[i] = tmp[k];
    }
};
