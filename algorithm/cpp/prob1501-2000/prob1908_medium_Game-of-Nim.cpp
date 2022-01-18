
#include <vector>

using namespace std;

class Solution {
public:
    bool nimGame(vector<int>& piles) {
        int n = piles.size();
        vector<int> dp(1 << (n * 3), -1);
        dp[0] = 0;
        int t = 0;
        for(int i = 0; i < n; ++i)
            t += (piles[i] << (3 * i));
        return solve(t, n, dp) == 1;
    }

private:
    int solve(int s, const int n, vector<int>& dp)
    {
        if(dp[s] != -1)
            return dp[s];
        for(int i = 0; i < n; ++i)
        {
            int m = ((s >> (i * 3)) & 7);
            for(int j = 0; j < m; ++j)
            {
                int t = s & (~(7 << (i * 3)));
                t += j << (i * 3);
                if(solve(t, n, dp) == 0)
                    return dp[s] = 1;
            }
        }
        return dp[s] = 0;
    }
};
