// prob410: Split Array Largest Sum

/*
 * Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty
 * continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays
 * Note:
 * If n is the length of array, assume the following constraints are satisfied:
 * 1 ≤ n ≤ 1000
 * 1 ≤ m ≤ min(50, n)
 */

/*
 * Examples:
 * Input:
 * nums = [7,2,5,10,8]
 * m = 2
 * Output:
 * 18
 * Explanation:
 * There are four ways to split nums into two subarrays.
 * The best way is to split it into [7,2,5] and [10,8],
 * where the largest sum among the two subarrays is only 18.
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<ll> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];
        if(m == 1) return sums[n];
        vector<vector<int> > dp(n + 1, vector<int>(m + 1, INT_MAX));
        _solve(nums, 0, m, sums, dp);
        return dp[0][m];
    }

private:
    using ll = long long;

    void _solve(const vector<int>& nums, int left, int m, const vector<ll>& sums, vector<vector<int> >& dp)
    {
        // dp[left][m] := [left..n-1] 分割为 m 份的答案(各个段和中最大值的最小值)
        int n = nums.size();
        int len = n - left;
        if(len < m)
        {
            dp[left][m] = -1;
            return;
        }
        if(dp[left][m] != INT_MAX) return;
        if(m == 1)
        {
            int cur_sum = sums[n] - sums[left];
            dp[left][m] = cur_sum;
            return;
        }
        for(int i = left; i <= n - m; ++i)
        {
            int cur_sum = sums[i + 1] - sums[left];
            _solve(nums, i + 1, m - 1, sums, dp);
            if(dp[i + 1][m - 1] == -1) continue;
            dp[left][m] = min(dp[left][m], max(cur_sum, dp[i + 1][m - 1]));
        }
    }
};


class Solution_2 {
public:
    int splitArray(vector<int>& nums, int m) {
        using ll = long long;
        int n = nums.size();
        vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, INT_MAX));
        vector<ll> sums(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sums[i + 1] = sums[i] + nums[i];
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < i; k++) {
                    dp[i][j] = min(dp[i][j], max(dp[k][j - 1], sums[i] - sums[k]));
                }
            }
        }
        return dp[n][m];
    }
};

// 二分答案
class Solution_3 {
public:
    int splitArray(vector<int>& nums, int m) {
        int maxx = nums[0];
        ll sum = 0;
        for(int num: nums)
        {
            maxx = max(maxx, num);
            sum += num;
        }
        ll left = maxx, right = sum;
        while(left < right)
        {
            ll mid = left + (right - left) / 2;
            if(_check(nums, mid, m))
                left = mid + 1;
            else
                right = mid;
        }
        return (int)left;
    }

private:
    using ll = long long;

    bool _check(const vector<int>& nums, ll max_sum, int m)
    {
        int num = _partition(nums, max_sum, 0);
        // num > m: 要求分 m 块，最少要分 num 块，max_sum 选小了, left = mid + 1
        // num <= m: 要求分 m 块，最少要分 num 块，max_sum 以及更大值可以满足，继续试更小值能否满足, right = mid
        return num > m;
    }

    int _partition(const vector<int>& nums, ll max_sum, int left)
    {
        // 最大和 max_sum, [left..n-1] 最少分几段
        // maxx <= max_sum <= sums
        int n = nums.size();
        if(left == n) return 0;
        ll sum = nums[left];
        int right = left + 1;
        while(right < n && sum + nums[right] <= max_sum)
        {
            sum += nums[right];
            ++right;
        }
        return 1 + _partition(nums, max_sum, right);
    }
};
