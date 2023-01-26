// prob493: Reverse Pairs

/*
 * Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].
 * You need to return the number of important reverse pairs in the given array.
 */

/*
 * Example1:
 * Input: [1,3,2,3,1]
 * Output: 2
 * Example2:
 * Input: [2,4,3,5,1]
 * Output: 3
 */

/*
 * Note:
 * The length of the given array will not exceed 50,000.
 * All the numbers in the input array are in the range of 32-bit integer.
 */

#include <vector>
#include <algorithm>

using namespace std;

// 离散化 + 权值树状数组
class BIT {
public:
    BIT():cnts(1, 0){}
    BIT(int n):cnts(n + 1, 0){}

    void update(int index, int delta)
    {
        int n = cnts.size();
        while(index < n)
        {
            cnts[index] += delta;
            index += _lowbit(index);
        }
    }

    int query(int i)
    {
        int cnt = 0;
        while(i > 0)
        {
            cnt += cnts[i];
            i -= _lowbit(i);
        }
        return cnt;
    }

private:
    vector<int> cnts;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();

        vector<ll> x; // 离散化后的值
        for(int i: nums)
        {
            x.push_back(i);
            x.push_back(2ll * i);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());

        int m = x.size();
        BIT bit(m); // bit 内部对 m 做了 + 1
        bit.update(_find(nums[0], x), 1);
        int ans = 0;
        for(int i = 1; i < n; ++i)
        {
            ans += i - bit.query(_find(2ll * nums[i], x));
            bit.update(_find(nums[i], x), 1);
        }
        return ans;
    }

private:
    using ll = long long;

    int _find(ll v, const vector<ll>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin() + 1;
    }
};

// CDQ 分治
// Modified Merge Sort
// 在归并排序的归并阶段统计一些信息
// Ref 面51
class Solution_2 {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 0;
        return _mergesort(nums, 0, n - 1);
    }

private:
    using ll = long long;

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
        //-------------------
        // 统计过程
        int i = left, j = mid;
        int res = 0;
        while(i < mid && j <= right)
        {
            if((ll)nums[i] > 2ll * nums[j])
            {
                res += mid - i;
                ++j;
            }
            else
                ++i;
        }
        //-------------------

        // 归并过程
        i = left, j = mid;
        int k = 0;
        vector<int> tmp(right - left + 1, 0);
        while(i < mid && j <= right)
        {
            if(nums[i] > nums[j])
            {
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

class Solution_3 {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return 0;
        vector<ll> x; // 离散化后的值
        for(int i: nums)
        {
            x.push_back(i);
            x.push_back(2ll * i);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());

        int m = x.size();
        SegmentTree segmenttree;
        segmenttree.build(0, m - 1);
        segmenttree.add(_find(nums[0], x));
        int result = 0;
        for(int i = 1; i < n; ++i)
        {
            result += segmenttree.query(_find(2ll * nums[i], x) + 1, m - 1);
            segmenttree.add(_find(nums[i], x));
        }
        return result;
    }

private:
    using ll = long long;

    int _find(ll v, const vector<ll>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};
