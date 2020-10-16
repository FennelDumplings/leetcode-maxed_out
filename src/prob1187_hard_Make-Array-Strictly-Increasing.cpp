// prob1187: Make Array Strictly Increasing

/*
 * https://leetcode-cn.com/problems/make-array-strictly-increasing/
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        if(n <= 1) return 0;
        int m = arr2.size();
        if(m == 0)
        {
            for(int i = 1; i < n; ++i)
                if(arr1[i - 1] >= arr1[i])
                    return -1;
            return 0;
        }
        // n >= 2, m >= 1
        dp = vector<unordered_map<int, int>>(n);
        // dp[i][prev]
        sort(arr2.begin(), arr2.end());
        int minx_arr2 = arr2[0];
        int ans1 = solve(arr1, arr2, 1, arr1[0]);
        int ans2 = solve(arr1, arr2, 1, minx_arr2);
        if(ans1 == -1 && ans2 == -1) return -1;
        if(ans2 == -1) return ans1;
        if(ans1 == -1) return ans2 + 1;
        return min(ans1, ans2 + 1);
    }

private:
    vector<unordered_map<int, int>> dp;

    int solve(const vector<int>& arr1, const vector<int>& arr2, int i, int prev)
    {
        int n = arr1.size();
        if(i == n)
            return 0;

        if(dp[i].count(prev))
            return dp[i][prev];

        dp[i][prev] = -1;

        if(prev < arr1[i])
        {
            // 可以不改
            int ans1 = solve(arr1, arr2, i + 1, arr1[i]);
            if(ans1 != -1)
                dp[i][prev] = ans1;
        }

        // [i..n-1] 中大于 prev 的最小的
        auto it = upper_bound(arr2.begin(), arr2.end(), prev);
        if(it == arr2.end() && prev >= arr1[i])
            return dp[i][prev];
        if(it != arr2.end() && arr1[i] != *it)
        {
            int ans2 = solve(arr1, arr2, i + 1, *it);
            if(ans2 != -1)
            {
                if(dp[i][prev] != -1)
                    dp[i][prev] = min(dp[i][prev], ans2 + 1);
                else
                    dp[i][prev] = ans2 + 1;
            }
        }

        return dp[i][prev];
    }
};
