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
