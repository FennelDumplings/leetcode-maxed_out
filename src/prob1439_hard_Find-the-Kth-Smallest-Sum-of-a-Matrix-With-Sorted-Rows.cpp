// prob1439: Find the Kth Smallest Sum of a Matrix With Sorted Rows

/*
 * https://leetcode-cn.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Item
{
    vector<int> idxs;
    int sum;
    Item(const vector<int>& idxs, int sum):idxs(idxs),sum(sum){}
};

struct HeapCmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.sum > i2.sum;
    }
};

const int MOD = 95191;
const int p = 12739;
using ll = long long;

struct MyHash
{
    int operator()(const vector<int>& idxs) const
    {
        int hash = 0;
        for(int i: idxs)
        {
            hash = (hash * (ll)p) % MOD;
            hash = (hash + (ll)i) % MOD;
        }
        return hash;
    }
};

class Solution_2 {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int n = mat.size(), m = mat[0].size();
        int sum = 0;
        for(int i = 0; i < n; ++i)
            sum += mat[i][0];
        vector<int> idxs(n, 0);
        priority_queue<Item, vector<Item>, HeapCmp> pq;
        pq.push(Item(idxs, sum));
        unordered_set<vector<int>, MyHash> setting;
        setting.insert(idxs);
        while(!pq.empty() && k > 0)
        {
            vector<int> nxt_idxs = pq.top().idxs;
            int cur_sum = pq.top().sum;
            pq.pop();
            --k;
            if(k == 0)
                return cur_sum;
            for(int i = 0; i < n; ++i)
            {
                int j = nxt_idxs[i];
                if(j + 1 == m) continue;
                int nxt_sum = cur_sum - mat[i][j] + mat[i][j + 1];
                nxt_idxs[i] = j + 1;
                if(setting.count(nxt_idxs) == 0)
                {
                    setting.insert(nxt_idxs);
                    pq.push(Item(nxt_idxs, nxt_sum));
                }
                nxt_idxs[i] = j;
            }
        }
        return -1;
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        start_sum = 0;
        int n = mat.size(), m = mat[0].size();
        int right = 0;
        for(int i = 0; i < n; ++i)
        {
            right += mat[i][m - 1];
            start_sum += mat[i][0];
        }
        int left = start_sum;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            int cnt = check(mat, mid, k);
            if(cnt >= k)
                right = mid - 1;
            else
                left = mid;
        }
        return left;
    }

private:
    int start_sum;

    int check(const vector<vector<int>>& mat, int mid, int k)
    {
        // ans: 于 mid 的个数
        // ans >= k，可以早停
        int ans = 1;
        dfs(mat, 0, start_sum, ans, mid, k);
        return ans;
    }

    // dfs 参数迭代 i，内部迭代 j (i, j) 对应
    void dfs(const vector<vector<int>>& mat, int i, int sum, int& cnt, const int mid, const int k)
    {
        // 推进 mat 第 i 行的 j
        // sum 是在 [0..i-1] 行已经选了某些点的情况下的和
        // 此时 [i..n-1] 行仍然是用的 mat[i..n-1][0]，即没有在前 i 行做 sum 代表的的选择下选
        int n = mat.size(), m = mat[0].size();
        // 剪枝
        if(sum >= mid || cnt >= k || i == n)
            return;
        // sum < mid, cnt < k, i < n
        // sum 是个合法选择
        // sum 代表的选择在调用方已经计了 cnt
        // 在 sum 选择下先搜索下一行
        dfs(mat, i + 1, sum, cnt, mid, k);
        // 在回溯阶段推进本行的 j
        int j = 1;
        sum -= mat[i][0];
        while(j < m && sum + mat[i][j] < mid)
        {
            ++cnt;
            dfs(mat, i + 1, sum + mat[i][j], cnt, mid, k);
            ++j;
        }
    }
};
