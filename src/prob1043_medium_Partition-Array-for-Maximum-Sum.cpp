// prob1043: Partition Array for Maximum Sum

/*
 * https://leetcode-cn.com/problems/partition-array-for-maximum-sum/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n + 1, INT_MIN);
        dp[0] = 0;
        for(int i = 1; i <= n; ++i)
        {
            int j = i;
            int maxx = arr[j - 1];
            while(j >= max(1, i - k + 1))
            {
                maxx = max(maxx, arr[j - 1]);
                dp[i] = max(dp[i], dp[j - 1] + (i - j + 1) * maxx);
                --j;
            }
        }
        return dp[n];
    }
};
