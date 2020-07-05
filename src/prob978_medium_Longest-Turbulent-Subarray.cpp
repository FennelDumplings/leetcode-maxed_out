// prob978: Longest Turbulent Subarray

/*
 * https://leetcode-cn.com/problems/longest-turbulent-subarray/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxTurbulenceSize(vector<int>& A) {
        if(A.empty()) return 0;
        int n = A.size();
        vector<int> dp(n, 1);
        for(int i = 1; i < n; ++i)
        {
            if(A[i] == A[i - 1]) continue;
            ++dp[i];
            if(dp[i - 1] == 1) continue;
            if(A[i - 2] < A[i - 1] && A[i - 1] > A[i])
                dp[i] += dp[i - 1] - 1;
            if(A[i - 2] > A[i - 1] && A[i - 1] < A[i])
                dp[i] += dp[i - 1] - 1;
        }
        int ans = 0;
        for(int i: dp)
            ans = max(ans, i);
        return ans;
    }
};
