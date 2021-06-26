// prob1157: Online Majority Element In Subarray

/*
 * Implementing the class MajorityChecker, which has the following API:
 * MajorityChecker(int[] arr) constructs an instance of MajorityChecker with the given array arr;
 * int query(int left, int right, int threshold) has arguments such that:
 * 0 <= left <= right < arr.length representing a subarray of arr;
 * 2 * threshold > right - left + 1, ie. the threshold is always a strict majority of the length of the subarray
 * Each query(...) returns the element in arr[left], arr[left+1], ..., arr[right] that occurs at least threshold times, or -1 if no such element exists.
 */

/*
 * Example:
 * MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
 * majorityChecker.query(0,5,4); // returns 1
 * majorityChecker.query(0,3,3); // returns -1
 * majorityChecker.query(2,3,2); // returns 2
 */

/*
 * Constraints:
 * 1 <= arr.length <= 20000
 * 1 <= arr[i] <= 20000
 * For each query, 0 <= left <= right < len(arr)
 * For each query, 2 * threshold > right - left + 1
 * The number of queries is at most 10000
 */

#include <random>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <cmath>

using namespace std;

// 随机化
// 在 STL 容器中随机选择
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator *g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(*g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, &gen);
}
class MajorityChecker {
public:
    MajorityChecker(vector<int>& arr):arr(arr) {
        mapping = vector<vector<int>>(20001); // num -> 有序 idxs
        int n = arr.size();
        for(int i = 0; i < n; ++i)
            mapping[arr[i]].push_back(i);
    }

    int query(int left, int right, int threshold) {
        int cnt  = 0;
        for(int i = 0; i < N; ++i)
        {
            auto it = select_randomly(arr.begin() + left, arr.begin() + right + 1);
            int cand = *it;
            auto it_left = lower_bound(mapping[cand].begin(), mapping[cand].end(), left);
            auto it_right = upper_bound(mapping[cand].begin(), mapping[cand].end(), right);
            if(it_right - it_left >= threshold)
                return cand;
        }
        return -1;
    }

private:
    vector<vector<int>> mapping; // num -> 有序 idxs
    vector<int> arr;
    int N = 10;
};


// 划分树区间第 k 大
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


class MajorityChecker {
public:
    MajorityChecker(vector<int>& arr):arr(arr) {
        if(arr.empty()) return;
        // mapping = unordered_map<int, vector<int>>(); // num -> 有序 idxs
        mapping = vector<vector<int>>(20001); // num -> 有序 idxs
        int n = arr.size();
        for(int i = 0; i < n; ++i)
            mapping[arr[i]].push_back(i);
        partitiontree = PartitionTree();
        partitiontree.build(0, n - 1, arr);
    }

    int query(int left, int right, int threshold) {
        // right + 1 - (right - left + 1) / 2 - left
        int k = right + 1 - (right - left + 1) / 2 - left;
        int cand = partitiontree.query(left, right, k);
        auto it_left = lower_bound(mapping[cand].begin(), mapping[cand].end(), left);
        auto it_right = upper_bound(mapping[cand].begin(), mapping[cand].end(), right);
        if(it_right - it_left >= threshold)
            return cand;
        return -1;
    }

private:
    // unordered_map<int, vector<int>> mapping; // num -> 有序 idxs
    vector<vector<int>> mapping; // num -> 有序 idxs
    PartitionTree partitiontree;
    vector<int> arr;
};


// 分块
class Block
{
public:
    void build(const vector<int>& nums)
    {
        this -> nums = nums;
        n = nums.size();
        bs = floor(sqrt(n));
        nb = n / bs + 1;
        dp = vector<vector<int>>(nb, vector<int>(nb, 0));
        mapping = vector<vector<int>>(20001);

        for(int i = 0; i < n; ++i)
            mapping[nums[i]].push_back(i);

        vector<int> cnts(20001); // num -> cnt;
        for(int block_l = 0; block_l < nb; ++block_l)
        {
            cnts.clear();
            int max_cnt = 0;
            int max_num = 0; // dp[block_l][block_r];
            for(int i = block_l * bs; i < n; ++i)
            {
                int num = nums[i];
                ++cnts[num];
                if(cnts[num] > max_cnt)
                {
                    max_cnt = cnts[num];
                    max_num = num;
                    dp[block_l][i / bs] = max_num;
                }
            }
        }
    }

    int query(int l, int r, int threshold)
    {
        int block_l = l / bs, block_r = r / bs;
        int L = block_l, R = block_r;
        if(block_l * bs < l || r < ((block_l + 1) * bs - 1))
        {
            ++L;
            for(int i = l; i < min((block_l + 1) * bs, n); ++i)
            {
                int cand = nums[i];
                auto it_left = lower_bound(mapping[cand].begin(), mapping[cand].end(), l);
                auto it_right = upper_bound(mapping[cand].begin(), mapping[cand].end(), r);
                if(it_right - it_left >= threshold)
                    return cand;
            }
        }
        if(block_r != block_l)
        {
            if(r < (block_r + 1) * bs - 1)
            {
                --R;
                for(int i = block_r * bs; i <= min((block_r + 1) * bs - 1, r); ++i)
                {
                    int cand = nums[i];
                    auto it_left = lower_bound(mapping[cand].begin(), mapping[cand].end(), l);
                    auto it_right = upper_bound(mapping[cand].begin(), mapping[cand].end(), r);
                    if(it_right - it_left >= threshold)
                        return cand;
                }
            }
        }
        if(L <= R)
        {
            int cand = dp[L][R];
            auto it_left = lower_bound(mapping[cand].begin(), mapping[cand].end(), l);
            auto it_right = upper_bound(mapping[cand].begin(), mapping[cand].end(), r);
            if(it_right - it_left >= threshold)
                return cand;
        }
        return -1;
    }

private:
    vector<int> nums;
    vector<vector<int>> dp; // dp[block_l][block_r] := 块 block_l ~ block_r 的众数
    vector<vector<int>> mapping; // num -> 有序 idxs
    int nb, bs, n;
};

class MajorityChecker {
public:
    MajorityChecker(vector<int>& arr) {
        block = Block();
        block.build(arr);
    }

    int query(int left, int right, int threshold) {
        return block.query(left, right, threshold);
    }

private:
    Block block;
        n = nums.size();
};

// 摩尔投票+线段树
struct STNode
{
    int nodeLeft, nodeRight;
    int cand, cnt;
    STNode *left, *right;
    STNode(int l, int r, int cand, int cnt, STNode* left=nullptr, STNode* right=nullptr)
        :nodeLeft(l),nodeRight(r),cand(cand),cnt(cnt),left(left),right(right){}
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

    void build(const vector<int>& nums)
    {
        int n = nums.size();
        root = _build(0, n - 1, nums);
    }

    int query(int l, int r)
    {
        PII item = _query(root, l, r);
        return item.first;
    }

private:
    STNode *root;
    using PII = pair<int, int>;

    PII _query(STNode* node, int l, int r)
    {
        int nodeLeft = node -> nodeLeft, nodeRight = node -> nodeRight;
        // [l, r], [nodeLeft, nodeRight]
        if(l == nodeLeft && r == nodeRight)
            return PII(node -> cand, node -> cnt);
        int nodeMid = (nodeLeft + nodeRight) / 2;
        if(r <= nodeMid)
            return _query(node -> left, l, r);
        else if(nodeMid < l)
            return _query(node -> right, l, r);
        else
        {
            PII item1 = _query(node -> left, l, nodeMid);
            PII item2 = _query(node -> right, nodeMid + 1, r);
            int cand1 = item1.first, cnt1 = item1.second;
            int cand2 = item2.first, cnt2 = item2.second;
            if(cand1 == cand2)
                return PII(cand1, cnt1 + cnt2);
            int cand, cnt;
            if(cnt1 >= cnt2)
            {
                cand = cand1;
                cnt = cnt1 - cnt2;
            }
            else
            {
                cand = cand2;
                cnt = cnt2 - cnt1;
            }
            return PII(cand, cnt);
        }
    }


    STNode* _build(int nodeLeft, int nodeRight, const vector<int>& nums)
    {
        if(nodeLeft == nodeRight)
        {
            return new STNode(nodeLeft, nodeRight, nums[nodeLeft], 1);
        }
        int nodeMid = (nodeLeft + nodeRight) / 2;
        STNode* left = _build(nodeLeft, nodeMid, nums);
        STNode* right = _build(nodeMid + 1, nodeRight, nums);
        int cand1 = left -> cand, cnt1 = left -> cnt;
        int cand2 = right -> cand, cnt2 = right -> cnt;
        if(cand1 == cand2)
        {
            return new STNode(nodeLeft, nodeRight, cand1, cnt1 + cnt2, left, right);
        }
        else
        {
            int cand, cnt;
            if(cnt1 >= cnt2)
            {
                cand = cand1;
                cnt = cnt1 - cnt2;
            }
            else
            {
                cand = cand2;
                cnt = cnt2 - cnt1;
            }
            return new STNode(nodeLeft, nodeRight, cand, cnt, left, right);
        }
    }
};

class MajorityChecker {
public:
    MajorityChecker(vector<int>& arr) {
        int n = arr.size();
        mapping = vector<vector<int>>(20001);
        for(int i = 0; i < n; ++i)
            mapping[arr[i]].push_back(i);
        sttree = SegmentTree();
        sttree.build(arr);
    }

    int query(int left, int right, int threshold) {
        int cand = sttree.query(left, right);
        auto it_left = lower_bound(mapping[cand].begin(), mapping[cand].end(), left);
        auto it_right = upper_bound(mapping[cand].begin(), mapping[cand].end(), right);
        if(it_right - it_left >= threshold)
            return cand;
        else
            return -1;
    }

private:
    SegmentTree sttree;
    vector<vector<int>> mapping; // num -> 有序 idxs
};



// ---------------------------------------------------------------------------------------------------------

// 树套树做法
// https://leetcode-cn.com/problems/online-majority-element-in-subarray/solution/wu-nao-shu-ju-jie-gou-zuo-fa-shu-tao-shu-by-wnjxyk/

// ZKW线段树
// https://leetcode-cn.com/problems/online-majority-element-in-subarray/solution/you-ya-qie-gao-xiao-de-jie-fa-zkwxian-duan-shu-by-/
class MajorityChecker {
public:
    MajorityChecker(vector<int>& arr) {
        num = arr.size() + 2;	//zkw线段树的查询需要按开区间，故需要在原数组两端各扩充一个元素
		while(treeSize < num)
			treeSize <<= 1;
		for(int i = 0; i < arr.size(); i++){
			segmentTree[treeSize + i + 1] = (1 << 16) + arr[i];	//所有输入的arr[i] <= 20000, 数组大小 <= 20000 用一个int的高低16位分别表示绝对众数的值和绝对出现次数
            numindex[arr[i]].push_back(i);
        }
		for(int i = treeSize - 1; i >= 1; i--)
            segmentTree[i] = merge(segmentTree[2 * i], segmentTree[2 * i + 1]);
    }
    int query(int left, int right, int threshold) {
		int result = 0;
        for(int s = left + treeSize, t = right + treeSize + 2; s^t^1; s >>= 1, t >>= 1){
			if(~s & 1)
				result = merge(result, segmentTree[s + 1]);
			if(t & 1)
				result = merge(result, segmentTree[t - 1]);
		}
        if(result >> 16 > 0){
            auto it_left = lower_bound(numindex[result % 65536].begin(),numindex[result % 65536].end(), left);
            auto it_right = upper_bound(numindex[result % 65536].begin(),numindex[result % 65536].end(), right);
            if(it_right - it_left >= threshold)
                return result % 65536;
        }
		return -1;
    }
private:
    inline int merge(const int l, const int r){
        return (l >> 16 > r >> 16 ? l % 65536 : r % 65536) + ((l % 65536 == r % 65536 ? (l >> 16) + (r >> 16) : abs((l >> 16) - (r >> 16))) << 16);
    }
	int treeSize = 1;
	int num = 0;
	int segmentTree[65536] = {0};
    unordered_map<int, vector<int>> numindex;
};


// 主席树
// https://leetcode-cn.com/problems/online-majority-element-in-subarray/solution/ke-chi-jiu-hua-xian-duan-shu-zhu-xi-shu-by-lannnnh/
class MajorityChecker {
    #define N 20010
    int rt[N],sum[N<<5],lc[N<<5],rc[N<<5],data[N];
    int t=0,len=0;
    void build(int &n,int left,int right){
        n=++t;
        sum[t]=0;
        if(left==right)
            return;
        int mid=left+(right-left)/2;
        build(lc[n],left,mid);
        build(lc[n],mid+1,right);
    }
    int update(int o,int left,int right,int id){
        int oo=++t;
        sum[oo]=sum[o]+1;
        if(right==left)
            return oo;
        lc[oo]=lc[o];
        rc[oo]=rc[o];
        int mid=left+(right-left)/2;
        if(mid>=id){
            lc[oo]=update(lc[o],left,mid,id);
        }else{
            rc[oo]=update(rc[o],mid+1,right,id);
        }
        return oo;
    }
   int query(int pre,int cur,int left,int right,int k ){
        if(left==right){
            return data[left];
        }
        int mid=left+(right-left)/2;
        if(sum[lc[cur]]-sum[lc[pre]]>=k){
            return query(lc[pre],lc[cur],left,mid,k);
        }else if(sum[rc[cur]]-sum[rc[pre]]>=k){
            return query(rc[pre],rc[cur],mid+1,right,k);
        }else{
            return -1;
        }
    }

public:
    MajorityChecker(vector<int>& arr) {
      for(int i=0;i<arr.size();i++){
          data[i+1]=arr[i];
      }
      sort(data+1,data+1+arr.size());
      len=unique(data+1,data+1+arr.size())-data-1;
      unordered_map<int,int> log;
      for(int i=1;i<=len;i++)
          log[data[i]]=i;
      build(rt[0],1,len);
      for(int i=0;i<arr.size();i++){
          rt[i+1]=update(rt[i],1,len,log[arr[i]]);
      }
    }

    int query(int left, int right, int threshold) {
        return query(rt[left],rt[right+1],1,len,threshold);

    }
};
