// prob215: Kth Largest Element in an Array

/*
 * Find the kth largest element in an unsorted array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 */

/*
 * Example 1:
 * Input: [3,2,1,5,6,4] and k = 2
 * Output: 5
 * Example 2:
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4
 * Output: 4
 */

/*Note:
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 */

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 1) return nums[0];
        // return heapk(nums, k);
        return partition(nums, k, 0, n - 1);
    }

private:
    int partition(vector<int>& nums, int k, int left, int right)
    {
        // 在 nums 的 [left .. right] 中找第 k 大
        int randIdx = rand() % (right - left + 1) + left; // 随机选择 pivot
        _swap(nums, randIdx, left);
        int pivot = nums[left];
        int l = left, r = right;
        while(l < r)
        {
            while(l < r && nums[r] <= pivot)
                --r;
            if(l < r)
            {
                nums[l] = nums[r];
                ++l;
            }
            while(l < r && nums[l] >= pivot)
                ++l;
            if(l < r)
            {
                nums[r] = nums[l];
                --r;
            }
        }
        nums[l] = pivot;
        if(l == left + k - 1)
            return nums[l];
        else if(l < left + k - 1)
            return partition(nums, k - (l - left + 1), l + 1, right);
        else
            return partition(nums, k, left, l - 1);
    }

    void _swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    int heapk(vector<int>& nums, int k)
    {
        // 建堆 make_heap()
        // 添加 push_heap()
        // 删除 pop_heap()
        // 堆排序 sort_heap()
        vector<int> heap(k, 0);
        int n = nums.size();
        for(int i = 0; i < k; ++i)
            heap[i] = nums[i];
        make_heap(heap.begin(), heap.end(), greater<int>());
        pop_heap(heap.begin(), heap.end(), greater<int>());
        for(int i = k; i < n; ++i)
        {
            if(heap.back() < nums[i])
            {
                heap.pop_back();
                heap.push_back(nums[i]);
                push_heap(heap.begin(), heap.end(), greater<int>());
                pop_heap(heap.begin(), heap.end(), greater<int>());
            }
        }
        return heap.back();
    }
};

// 归并树
struct MTNode
{
    int start, end;
    vector<int> data;
    MTNode *left, *right;
    MTNode(int s, int e, const vector<int>& nums, MTNode* l=nullptr, MTNode* r=nullptr)
        :start(s),end(e),data(nums),left(l),right(r) {}
    ~MTNode()
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

class MergeTree
{
public:
    MergeTree()
    {
        root = nullptr;
    }

    ~MergeTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void build(int start, int end, const vector<int>& nums)
    {
        root = _build(start, end, nums);
    }

    int query(int i, int j, int k)
    {
        if(i > j) return 0;
        int result = 0;
        _query(root, i, j, k, result);
        return result;
    }

    int get(int i)
    {
        return (root -> data)[i];
    }

private:
    MTNode *root;

    void _query(MTNode* root, int i, int j, int k, int& result)
    {
        if(root -> start == i && root -> end == j)
        {
            auto pos = upper_bound((root -> data).begin(), (root -> data).end(), k);
            result += (root -> data).end() - pos;
            return;
        }
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(j <= mid)
        {
            _query(root -> left, i, j, k, result);
            return;
        }
        if(i > mid)
        {
            _query(root -> right, i, j, k, result);
            return;
        }
        _query(root -> left, i, mid, k, result);
        _query(root -> right, mid + 1, j, k, result);
    }

    MTNode* _build(int start, int end, const vector<int>& nums)
    {
        if(start == end)
        {
            return new MTNode(start, end, vector<int>({nums[start]}));
        }
        int mid = start + (end - start) / 2;
        MTNode *left = _build(start, mid, nums);
        MTNode *right = _build(mid + 1, end, nums);
        vector<int> merged((left -> data).size() + (right -> data).size());
        merge((left -> data).begin(), (left -> data).end(), (right -> data).begin(), (right -> data).end(), merged.begin());
        MTNode *cur = new MTNode(start, end, merged, left, right);
        return cur;
    }
};

class Solution_3 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 1) return nums[0];
        MergeTree mergetree;
        mergetree.build(0, n - 1, nums);
        int left = mergetree.get(0), right = mergetree.get(n - 1);
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            int cnt = mergetree.query(0, n - 1, mid); // > mid 的元素个数
            if(cnt == k - 1)
                return mid;
            else if(cnt > k - 1)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
};

// 划分树
struct PTNode
{
    int start, end;
    vector<int> nums, toleft;
    PTNode *left, *right;
    PTNode(int s, int e, PTNode* l=nullptr, PTNode* r=nullptr)
        :start(s),end(e),nums(vector<int>(end - start + 1)),toleft(vector<int>(end - start + 2)),left(l),right(r) {}
    ~PTNode()
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

class PartitionTree
{
public:
    PartitionTree()
    {
        root = nullptr;
        sorted = vector<int>();
    }

    ~PartitionTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void build(int start, int end, const vector<int>& nums)
    {
        sorted = nums;
        sort(sorted.begin(), sorted.end());
        root = new PTNode(start, end);
        root -> nums = nums;
        _build(root);
    }

    int query(int i, int j, int k)
    {
        if(i > j) return 0;
        return _query(root, i, j, k);
    }

private:
    PTNode *root;
    vector<int> sorted;

    int _query(PTNode* root, int i, int j, int k)
    {
        if(root -> start == root -> end) return (root -> nums)[0];

        int tli = 0;
        if(root -> start != i)
            tli = (root -> toleft)[i - root -> start];
        int tlj = (root -> toleft)[j - root -> start + 1];
        int tl = tlj - tli;
        int new_i, new_j;
        if(tl >= k)
        {
            // 第 k 大在左子
            new_i = root -> start + tli;
            new_j = new_i + tl - 1;
            return _query(root -> left, new_i, new_j, k);
        }
        else
        {
            // 第 k 大在右子
            int mid = root -> start + (root -> end - root -> start) / 2;
            new_i = mid + 1 + i - (root -> start) - tli;
            new_j = new_i + j - i - tl;
            return _query(root -> right, new_i, new_j, k - tl);
        }
    }

    void _build(PTNode* root)
    {
        if(root -> start == root -> end)
            return;
        int mid = root -> start + (root -> end - root -> start) / 2;
        int median =  sorted[mid];
        PTNode *left = new PTNode(root -> start, mid);
        PTNode *right = new PTNode(mid + 1, root -> end);
        int n = (root -> nums).size();
        int median_to_left = mid - root -> start + 1;
        for(int i = 0; i < n; ++i)
        {
            if((root -> nums)[i] < median)
                --median_to_left;
        }
        // 出循环后 median_to_left 为去往左子树中等于中位数的个数
        int to_left = 0; // 去往左子树的个数
        int idx_left = 0, idx_right = 0;
        for(int i = 0; i < n; ++i)
        {
            int cur = (root -> nums)[i];
            if(cur < median || ((cur == median) && median_to_left > 0))
            {
                (left -> nums)[idx_left] = cur;
                ++idx_left;
                ++to_left;
                if(cur == median)
                    --median_to_left;
            }
            else
            {
                (right -> nums)[idx_right] = cur;
                ++idx_right;
            }
            (root -> toleft)[i + 1] = to_left;
        }
        _build(left);
        _build(right);
        root -> left = left;
        root -> right = right;
    }
};

class Solution_4 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 1) return nums[0];
        PartitionTree partitiontree;
        partitiontree.build(0, n - 1, nums);
        return partitiontree.query(0, n - 1, n + 1 - k);
    }
};

// 二分
class Solution_5 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return topk(nums, n + 1 - k);
    }

private:
    int topk(const vector<int>& nums, int k)
    {
        // 从小到大排第 k
        int n = nums.size();
        int maxx = nums[0], minx = nums[0];
        for(int i = 1; i < n; ++i)
        {
            maxx = max(maxx, nums[i]);
            minx = min(minx, nums[i]);
        }
        int left = minx, right = maxx;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            int x = check(nums, mid);
            if(x >= k)
                right = mid - 1;
            else
                left = mid;
        }
        return left;
    }

    int check(const vector<int>& nums, int mid)
    {
        int ans = 0;
        for(int i: nums)
            if(i < mid)
                ++ans;
        return ans;
    }
};
