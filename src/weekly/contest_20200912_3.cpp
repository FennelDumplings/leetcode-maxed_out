
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumOperations(string leaves) {
        int n = leaves.size();
        // R[i] := [i..n-1] 上 y 的数量
        // L[i] := [0..i] 上 y 的数量
        vector<int> R(n, 0);
        vector<int> L(n, 0);
        if(leaves[0] == 'y')
            L[0] = 1;
        for(int i = 1; i < n; ++i)
        {
            L[i] = L[i - 1];
            if(leaves[i] == 'y')
                ++L[i];
        }
        if(leaves[n - 1] == 'y')
            R[n - 1] = 1;
        for(int i = n - 2; i >= 0; --i)
        {
            R[i] = R[i + 1];
            if(leaves[i] == 'y')
                ++R[i];
        }
        vector<int> dp(n, 0);
        // dp[i] := [0..j-1][j..i] 时候的最小次数
        // i = 1..n-2
        dp[1] = L[0];
        if(leaves[1] == 'r')
            ++dp[1];
        for(int i = 2; i <= n - 2; ++i)
        {
            dp[i] = min(dp[i - 1], L[i - 1]);
            if(leaves[i] == 'r')
                ++dp[i];
        }
        int ans = dp[1] + R[2];
        for(int i = 2; i <= n - 2; ++i)
        {
            ans = min(ans, dp[i] + R[i + 1]);
        }
        return ans;
    }
};
