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

// 平衡树
// 利用二叉搜索树的特性：左边节点的值小于等于当前节点值，右边节点的值大于等于当前节点值。
// 那么实现算法首先要构建一颗二叉搜索树：
// 1. 定义树的节点结构 TreeNode
// 2. 实现树的节点插入方法 insertNode
// 其中， insertNode 方法需要实现几个功能：
// 1. 构建二叉树
// 2. 维护每个节点中其左子树节点数量值 count：如果新加入的节点需要加入当前节点的左子树，则当前节点的 count += 1
// 3. 计算出新加入节点 nums[i] 的 "右侧小于当前元素的个数"，即题目所求值 res[i]

// 0. BST
struct BSTNode
{
    int data;
    BSTNode *left;
    BSTNode *right;
    int size;
    BSTNode():left(nullptr),right(nullptr){}
    BSTNode(const int& x, BSTNode* p=nullptr, BSTNode* q=nullptr, int s=1):data(x),left(p),right(q),size(s){}
    ~BSTNode()
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

class BinarySearchTree
{
public:
    BinarySearchTree():root(nullptr){}
    ~BinarySearchTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    bool find(const int& x) const
    {
        return find(x, root);
    }

    void insert(const int& x)
    {
        insert(x, root);
    }

    void remove(const int& x)
    {
        remove(x, root);
    }

    int lessthan(const int& x) const
    {
        return lessthan(x, root);
    }

private:
    BSTNode *root;

    int lessthan(const int& x, BSTNode* t) const;
    void insert(const int& x, BSTNode*& t);
    void remove(const int& x, BSTNode*& t);
    BSTNode* find(const int& x, BSTNode* t) const;
};

int BinarySearchTree::lessthan(const int& x, BSTNode* t) const
{
    if(t -> data >= x)
    {
        if(!t -> left)
            return 0;
        return lessthan(x, t -> left);
    }
    // t -> data < x
    int ans = 1;
    if(t -> left)
        ans += t -> left -> size;
    if(t -> right)
        ans += lessthan(x, t -> right);
    return ans;
}

BSTNode* BinarySearchTree::find(const int& x, BSTNode* t) const
{
    if(t == nullptr) return nullptr;
    else if(t -> data > x) return find(x, t -> left);
    else if(t -> data < x) return find(x, t -> right);
    else return t;
}

void BinarySearchTree::insert(const int& x, BSTNode*& t)
{
    if(t == nullptr)
    {
        t = new BSTNode(x, nullptr, nullptr, 1);
        return;
    }
    ++(t -> size);
    if(t -> data > x)
        insert(x, t -> left);
    else
        insert(x, t -> right);
}

void BinarySearchTree::remove(const int& x, BSTNode*& t)
{
    if(t == nullptr) return;
    --(t -> size);
    if(x < t -> data)
        remove(x, t -> left);
    if(x > t -> data)
        remove(x, t -> right);
    if(x == t -> data)
    {
        // 找到被删节点 t
        if(t -> left != nullptr && t -> right != nullptr)
        {
            // t 有两个子节点
            BSTNode *successor = t -> right;
            while(successor -> left != nullptr)
                successor = successor -> left;
            t -> data = successor -> data;
            remove(t -> data, t -> right);
        }
        else
        {
            // t 只有 1 个子节点，或没有子节点
            BSTNode *oldNode = t;
            t = (t -> left != nullptr) ? t -> left : t -> right;
            delete oldNode;
        }
    }
}

class Solution_4 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.empty()) return {};
        int n = nums.size();
        vector<int> result(n);
        BinarySearchTree bst;
        result[n - 1] = 0;
        bst.insert(nums[n - 1]);
        for(int i = n - 2; i >= 0; --i)
        {
            result[i] = bst.lessthan(nums[i]);
            bst.insert(nums[i]);
        }
        return result;
    }
};



// 1. SBT
struct SBTNode
{
    int data;
    SBTNode *left;
    SBTNode *right;
    int size;
    SBTNode():left(nullptr),right(nullptr){}
    SBTNode(const int& x, SBTNode* p=nullptr, SBTNode* q=nullptr, int s=1):data(x),left(p),right(q),size(s){}
    ~SBTNode()
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

class SizeBalancedTree
{
public:
    SizeBalancedTree():root(nullptr){}
    ~SizeBalancedTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void insert(const int& x)
    {
        insert(x, root);
    }

    int lessthan(const int& x) const
    {
        return lessthan(x, root);
    }

private:
    SBTNode *root;

    int lessthan(const int& x, SBTNode* t) const;
    void insert(const int& x, SBTNode*& t);
    void maintain(SBTNode*& t, bool flag);

    void left_rotate(SBTNode*& t)
    {
        // 调用方保证 t -> right 存在
        SBTNode *tmp = t -> right;
        t -> right = tmp -> left;
        tmp -> left = t;
        tmp -> size = t -> size;
        t -> size = 1;
        if(t -> right)
            t -> size += t -> right -> size;
        if(t -> left)
            t -> size += t -> left -> size;
        t = tmp;
    }

    void right_rotate(SBTNode*& t)
    {
        // 调用方保证 t -> left 存在
        SBTNode *tmp = t -> left;
        t -> left = tmp -> right;
        tmp -> right = t;
        tmp -> size = t -> size;
        t -> size = 1;
        if(t -> right)
            t -> size += t -> right -> size;
        if(t -> left)
            t -> size += t -> left -> size;
        t = tmp;
    }
};

void SizeBalancedTree::maintain(SBTNode*& t, bool flag)
{
    if(!flag)
    {
        if((t -> left && t -> left -> left) && (!t -> right || t -> left -> left -> size > t -> right -> size))
        {
            right_rotate(t);
        }
        else
        {
            if((t -> left && t -> left -> right) && (!t -> right || t -> left -> right -> size > t -> right -> size))
            {
                left_rotate(t -> left);
                right_rotate(t);
            }
            else
                return;
        }
    }
    else
    {
        if((t -> right && t -> right -> right) && (!t -> left || t -> right -> right -> size > t -> left -> size))
        {
            left_rotate(t);
        }
        else
        {
            if((t -> right && t -> right -> left) && (!t -> left || t -> right -> left -> size > t -> left -> size))
            {
                right_rotate(t -> right);
                left_rotate(t);
            }
            else
                return;
        }
    }
    maintain(t -> left, false);
    maintain(t -> right, true);
    maintain(t, false);
    maintain(t, true);
}

int SizeBalancedTree::lessthan(const int& x, SBTNode* t) const
{
    if(t -> data >= x)
    {
        if(!t -> left)
            return 0;
        return lessthan(x, t -> left);
    }
    // t -> data < x
    int ans = 1;
    if(t -> left)
        ans += t -> left -> size;
    if(t -> right)
        ans += lessthan(x, t -> right);
    return ans;
}

void SizeBalancedTree::insert(const int& x, SBTNode*& t)
{
    if(t == nullptr)
    {
        t = new SBTNode(x, nullptr, nullptr, 1);
        return;
    }
    ++(t -> size);
    if(t -> data > x)
        insert(x, t -> left);
    else
        insert(x, t -> right);
    // maintain(t);
    maintain(t, x >= t -> data);
}


class Solution_5 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.empty()) return {};
        int n = nums.size();
        vector<int> result(n);
        SizeBalancedTree sbt;
        result[n - 1] = 0;
        sbt.insert(nums[n - 1]);
        for(int i = n - 2; i >= 0; --i)
        {
            result[i] = sbt.lessthan(nums[i]);
            sbt.insert(nums[i]);
        }
        return result;
    }
};

// vector
// 292ms
#include <deque>
class Solution_6 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.empty()) return {};
        int n = nums.size();
        vector<int> result(n);
        result[n - 1] = 0;
        vector<int> vec({nums[n - 1]});
        for(int i = n - 2; i >= 0; --i)
        {
            auto it = lower_bound(vec.begin(), vec.end(), nums[i]);
            result[i] = it - vec.begin();
            vec.insert(it, nums[i]);
        }
        return result;
    }
};

// deque
// 252ms
class Solution_7 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.empty()) return {};
        int n = nums.size();
        vector<int> result(n);
        result[n - 1] = 0;
        deque<int> deq({nums[n - 1]});
        for(int i = n - 2; i >= 0; --i)
        {
            auto it = lower_bound(deq.begin(), deq.end(), nums[i]);
            result[i] = it - deq.begin();
            deq.insert(it, nums[i]);
        }
        return result;
    }
};
