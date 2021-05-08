// Prob300: Longest Increasing Subsequence

/*Description
 * Given an unsorted array of integers, find the length of longest increasing subsequence.
*/


/*
 * Example:
 * Input: [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
 */

/*
 * Note:
 * There may be more than one LIS combination, it is only necessary for you to return the length.
 * Your algorithm should run in O(n2) complexity.
 *
 * Follow up:
 * Could you improve it to O(n log n) time complexity?
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 必须掌握的 O(N^2) 解法
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> dp(n, 1);
        int result = 0;
        for(int i = 0; i <= n - 1; ++i)
        {
            for(int j = 0; j <= i - 1; ++j)
            {
                if(nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            result = max(result, dp[i]);
        }
        return result;
    }
};

class Solution_2 {
public:
    // 二分的优化
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> vec; // vec[i] 是长度为 i 的 LIS 的最小结尾
         for(int i = 0; i < n; ++i)
        {
            // nums[i] 更新到 vec 中
            int p = lower_bound(vec.begin(), vec.end(), nums[i]) - vec.begin(); // lower_bound 得到的是可以插入 nums[i] 的最小的位置
            if((int)vec.size() > p)
                vec[p] = nums[i];
            else
                vec.push_back(nums[i]);
        }
        return (int)vec.size();
    }
};

class Solution_3 {
public:
    // 树状数组优化
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        for(int i : nums)
            x.push_back(i);
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end()); // 把实际值离散化
        m = x.size();
        bit.assign(m + 1, 0); // 树状数组初始化
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            int dp = getmax(find(nums[i]) - 1) + 1;
            ans = max(ans, dp);
            add(find(nums[i]), dp);
        }
        return ans;
    }

private:
    int m;
    vector<int> x; // 此数组用于求 nums 中的值离散化之后的值

    int find(int v) // 从 nums 的值找到对应的离散化之后的值
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin() + 1;
    }

    vector<int> bit; // 树状数组
    int lowbit(int x)
    {
        // 树状数组经典实现
        return x & (-x);
    }
    int getmax(int x)
    {
        // 树状数组经典实现
        int ma = 0;
        for(int i = x; i; i -= lowbit(i))
            ma = max(ma, bit[i]);
        return ma;
    }
    void add(int x, int v)
    {
        // 树状数组经典实现
        for(int i = x; i <= m; i += lowbit(i))
            bit[i] = max(bit[i], v);
    }
};


// 树状数组
class BIT_RMQ
{
public:
    BIT_RMQ():vec(1,0),a(1,0){}
    BIT_RMQ(int n):vec(n + 1, 0),a(n,0){}

    void update(int idx, int x)
    {
        // vec[idx] 管的是 [idx-lowbit[idx] + 1..idx] 这个区间
        // a[idx -  1] 改为 x
        // vec[idx]
        a[idx - 1] = x;
        vec[idx] = x;
        int n = a.size();
        for(int i = idx; i <= n; i += _lowbit(i))
        {
            for(int j = 1; j < _lowbit(i); j <<= 1)
            {
                // j < _lowbit(i) <= j - i < _lowbit(i) - i <= i - j > i - _lowbit(i)
                // i = 8，即改 vec[8]
                // 要看 vec[7] = i - 1
                //      vec[6] = i - 2
                //      vec[4] = i - 4
                vec[i] = max(vec[i], vec[i - j]);
            }
        }
    }

    int query(int l, int r)
    {
        // 直接看 vec[r] 不行
        // vec[r] 对应 [r - lowbit[r] + 1, r]
        int ans = a[r - 1];
        while(true)
        {
            ans = max(ans, a[r - 1]);
            if(l == r)
                break;
            --r;
            for(; r - _lowbit(r) >= l; r -= _lowbit(r))
                ans = max(ans, vec[r]);
        }
        return ans;
    }

    void view()
    {
        int n = a.size();
        for(int i = 0; i < n; ++i)
            cout << a[i] << " ";
        cout << endl;
        for(int i = 1; i <= n; ++i)
            cout << vec[i] << " ";
        cout << endl;
    }

private:
    vector<int> vec;
    vector<int> a;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};

class Solution_5 {
public:
    // 树状数组优化
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        for(int i : nums)
            x.push_back(i);
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end()); // 把实际值离散化
        m = x.size();
        BIT_RMQ rmq(m);
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            if(find(nums[i]) == 1)
            {
                ans = max(ans, 1);
                rmq.update(1, 1);
                continue;
            }
            int dp = rmq.query(1, find(nums[i]) - 1) + 1;
            ans = max(ans, dp);
            rmq.update(find(nums[i]), dp);
        }
        return ans;
    }

private:
    int m;
    vector<int> x; // 此数组用于求 nums 中的值离散化之后的值

    int find(int v) // 从 nums 的值找到对应的离散化之后的值
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin() + 1;
    }
};


//
class Solution_6 {
public:
    // 树状数组优化
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        for(int i : nums)
            x.push_back(i);
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end()); // 把实际值离散化
        m = x.size();
        dp.assign(m + 1, 0);
        bit.assign(m + 1, 0); // 树状数组初始化
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            int w_idx = find(nums[i]);
            int len = 1;
            if(w_idx > 0)
                len += query(1, w_idx);
            ans = max(ans, len);
            update(w_idx + 1, len);
        }
        return ans;
    }

private:
    vector<int> x; // 所有能值排序后去重
    vector<int> dp; // 权值数组
    int m; // 权值数组的长度

    vector<int> bit; // 权值数组的树状数组

    void update(int idx, int val)
    {
        dp[idx - 1] = val;
        bit[idx] = val;
        for(int i = idx; i <= m; i += lowbit(i))
        {
            for(int j = 1; j < lowbit(i); j <<= 1)
            {
                bit[i] = max(bit[i], bit[i - j]);
            }
        }
    }

    int query(int l, int r)
    {
        int ans = dp[r - 1];
        while(true)
        {
            for(; r - lowbit(r) + 1 > l; r -= lowbit(r))
                ans = max(ans, bit[r]);
            if(r - lowbit(r) + 1 == l)
            {
                ans = max(ans, bit[r]);
                return ans;
            }
            ans = max(ans, dp[r - 1]);
            --r;
        }
    }

    int lowbit(int v)
    {
        return v & (-v);
    }

    int find(int v)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }
};
