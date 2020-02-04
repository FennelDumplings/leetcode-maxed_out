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
