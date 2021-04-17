// prob1508: Range Sum of Sorted Subarray Sums

/*
 * https://leetcode-cn.com/problems/range-sum-of-sorted-subarray-sums/
 */

#include <vector>
#include <algorithm>

using namespace std;

// 排序
class Solution_2 {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        using ll = long long;
        const int MOD = 1e9 + 7;
        vector<int> prefix_sums(n + 1);
        for(int i = 1; i <= n; ++i)
            prefix_sums[i] = prefix_sums[i - 1] + nums[i - 1];
        vector<int> sums;
        for(int r = 1; r <= n; ++r)
        {
            // r-1: [0..n-1]
            for(int l = 0; l <= r - 1; ++l)
            {
                // l [l-1,r-1] r
                // (l, r]
                sums.push_back(prefix_sums[r] - prefix_sums[l]);
            }
        }
        sort(sums.begin(), sums.end());
        int ans = 0;
        for(int i = left - 1; i <= right - 1; ++i)
            ans = (ans + (ll)sums[i]) % MOD;
        return ans;
    }
};

// 二分 + 双指针
class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        prefix_sums = vector<int>(n + 1);
        for(int i = 1; i <= n; ++i)
            prefix_sums[i] = prefix_sums[i - 1] + nums[i - 1];
        sums = vector<int>(n + 2);
        for(int i = 1; i <= n + 1; ++i)
            sums[i] = sums[i - 1] + prefix_sums[i - 1];
        return subarray_sum_k(right) - subarray_sum_k(left - 1);
    }

private:
    vector<int> prefix_sums;
    vector<int> sums;
    using ll = long long;
    const int MOD = 1e9 + 7;

    int subarray_sum_k(int k)
    {
        // 找所有子串和中最小的 k 个的和

        // 先找第 k 小的子串和

        // 子串和的范围 [1, prefix_sums.back()]
        // 二分：1 <= t <= prefix_sums.back()

        // 问有多少个子串和 <= 目标值 t(mid)
        int n = prefix_sums.size() - 1;
        int left = 1, right = prefix_sums.back();
        int cnt = 0, sum = 0;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            // 求 < mid 的子串和个数 cnt 以及这些子串和的和 sum
            // 对每个 i
            // 找到最大的 j，sum(nums[i..j-1]) = prefix_sums[j-1] - prefix_sums[i-1] <= 目标值(mid)
            // 长 j-i，共 j-i 个子数组以 i 开头
            // i 和 j 可以用单串单向的双指针维护
            int i = 0, j = 0;
            cnt = 0, sum = 0;
            while(i < n)
            {
                while(j < n && prefix_sums[j + 1] - prefix_sums[i] < mid)
                    ++j;
                cnt += j - i;
                sum = (sum + sums[j + 1] - sums[i + 1] - prefix_sums[i] * (j - i) + MOD) % MOD;
                ++i;
            }
            if(cnt > k)
                right = mid - 1;
            else
                left = mid;
        }
        return sum + left * (k - cnt);
    }
};


// 多路归并
#include <queue>

struct List
{
    // 当前这一路的和 sum，已经当前索引 idx
    int sum;
    int idx;
    List(int sum, int idx):sum(sum),idx(idx){}
};

struct Cmp
{
    bool operator()(const List& l1, const List& l2) const
    {
        return l1.sum > l2.sum; // 最小堆
    }
};

class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        const int MOD = 1e9 + 7;
        using ll = long long;
        priority_queue<List, vector<List>, Cmp> pq;
        for(int i = 0; i < n; ++i)
            pq.push(List(nums[i], i));
        int ans = 0;
        for(int i = 1; i < left; ++i)
        {
            List cur = pq.top();
            pq.pop();
            if(cur.idx < n - 1)
                pq.push(List(cur.sum + nums[cur.idx + 1], cur.idx + 1));
        }
        for(int i = left; i <= right; ++i)
        {
            List cur = pq.top();
            pq.pop();
            ans = (ans + cur.sum) % MOD;
            if(cur.idx < n - 1)
                pq.push(List(cur.sum + nums[cur.idx + 1], cur.idx + 1));
        }
        return ans;
    }
};
