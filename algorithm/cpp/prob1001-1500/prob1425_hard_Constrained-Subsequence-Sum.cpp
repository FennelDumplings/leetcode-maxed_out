// prob1425: Constrained Subsequence Sum

/*
 * https://leetcode-cn.com/problems/constrained-subsequence-sum/
 */

#include <vector>
#include <deque>

using namespace std;


// dp[i] := [0..i] 且以 i 结尾的最大子序列和
// 初始化：dp[0] = nums[0]
// 答案：max(dp[i])
// dp[i] = nums[i] + max(dp[j])   max(0, i - K + 1) <= j < i (长为 K-1) 的滑窗

class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        int K = k + 1; // 窗长 K
        vector<int> dp(n);
        dp[0] = nums[0];
        deque<int> deq;
        deq.push_back(0);
        int ans = dp[0];
        for(int i = 1; i < n; ++i)
        {
            int mx = dp[deq.front()];
            dp[i] = nums[i] + max(0, mx);
            ans = max(ans, dp[i]);
            while(!deq.empty() && dp[deq.back()] <= dp[i])
                deq.pop_back();
            deq.push_back(i);
            // 队列中维护 [i - K + 2, i]  长度为 K - 1
            if(deq.front() <= i - K + 1)
                deq.pop_front();
        }
        return ans;
    }
};
