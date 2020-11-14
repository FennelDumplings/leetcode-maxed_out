// prob1218: Longest Arithmetic Subsequence of Given Difference

/*
 * https://leetcode-cn.com/problems/longest-arithmetic-subsequence-of-given-difference/
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution_2 {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        if(arr.empty()) return 0;
        int n = arr.size();
        vector<int> dp(n, 1);
        // dp[i] := [0..i] 且以 i 结尾，最长等差子序列
        for(int i = 1; i < n; ++i)
        {
            int mx = 0;
            for(int j = 0; j < i; ++j)
            {
                if(arr[j] + difference == arr[i])
                    mx = max(mx, dp[j]);
            }
            dp[i] = max(dp[i], mx + 1);
        }
        int ans = 1;
        for(int i: dp)
            ans = max(ans, i);
        return ans;
    }
};

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        if(arr.empty()) return 0;
        int n = arr.size();
        vector<int> dp(n, 1);
        // dp[i] := [0..i] 且以 i 结尾，最长等差子序列
        unordered_map<int, int> mapping;
        // mapping[x] := arr[i] 为 x 时，dp[i] 的最大值
        mapping[arr[0]] = 1;
        for(int i = 1; i < n; ++i)
        {
            // 问: dp[0..i-1] 上有没有 arr[i] - difference
            // 如果有，最大的那一个是多少
            if(mapping.count(arr[i] - difference) != 0)
                dp[i] = max(dp[i], 1 + mapping[arr[i] - difference]);
            mapping[arr[i]] = max(mapping[arr[i]], dp[i]);
        }
        int ans = 1;
        for(int i: dp)
            ans = max(ans, i);
        return ans;
    }
};
