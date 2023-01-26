// prob1340: Jump Game V

/*
 * https://leetcode-cn.com/problems/jump-game-v/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        if(arr.empty()) return 0;
        int n = arr.size();
        dp = vector<int>(n, -1);
        int ans = 1;
        for(int i = 0; i < n; ++i)
            if(dp[i] == -1)
                ans = max(ans, solve(arr, d, i));
        return ans;
    }

private:
    // dp[i] := 以 i 开头的最长路径
    vector<int> dp;

    int solve(const vector<int>& arr, const int d, int pos)
    {
        if(dp[pos] != -1)
            return dp[pos];
        dp[pos] = 0;
        int n = arr.size();
        for(int k = 1; k <= d; ++k)
        {
            int nxt = pos + k;
            if(nxt >= n || arr[pos] <= arr[nxt])
                break;
            dp[pos] = max(dp[pos], 1 + solve(arr, d, nxt));
        }
        for(int k = 1; k <= d; ++k)
        {
            int nxt = pos - k;
            if(nxt < 0 || arr[pos] <= arr[nxt])
                break;
            dp[pos] = max(dp[pos], 1 + solve(arr, d, nxt));
        }
        dp[pos] = max(1, dp[pos]);
        return dp[pos];
    }
};
