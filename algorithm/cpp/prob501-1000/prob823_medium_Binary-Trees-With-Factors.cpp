// prob823: Binary Trees With Factors

/*
 * https://leetcode-cn.com/problems/binary-trees-with-factors/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end());
        dp.assign(n, 1);
        int ans = 0;
        for(int i = 1; i < n; ++i)
        {
            int l = 0, r = i - 1;
            while(l <= r)
            {
                if(A[l] * A[r] == A[i])
                {
                    int delta = ((ll)dp[l] * dp[r]) % MOD;
                    dp[i] = (dp[i] + delta) % MOD;
                    if(l == r)
                        dp[i] = (dp[i] + delta) % MOD;
                    ++l;
                    --r;
                }
                else if(A[l] * A[r] > A[i])
                    --r;
                else
                    ++l;
            }
            ans = (ans + (ll)dp[i]) % MOD;
        }
        return ans;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    vector<int> dp;
};
