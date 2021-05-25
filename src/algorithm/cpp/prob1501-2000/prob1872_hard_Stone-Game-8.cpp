#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + stones[i - 1];
        vector<int> dp(n, INT_MIN / 2);
        dp[n - 1] = 0;
        int mx = sums[n] - dp[n - 1];
        for(int i = n - 2; i >= 0; --i)
        {
            dp[i] = mx;
            mx = max(mx, sums[i + 1] - dp[i]);
        }
        return dp[0];
    }
};
