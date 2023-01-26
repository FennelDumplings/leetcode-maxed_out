// prob1547: Minimum Cost to Cut a Stick

/*
 * https://leetcode-cn.com/problems/minimum-cost-to-cut-a-stick/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        sort(cuts.begin(), cuts.end());
        vector<int> vec(m + 1);
        int l = 0;
        for(int i = 0; i < m; ++i)
        {
            int len = cuts[i] - l;
            if(len <= 0)
                continue;
            vec[i] = len;
            l = cuts[i];
        }
        vec[m] = n - l;
        return solve(vec);
    }

private:
    int solve(const vector<int>& vec)
    {
        int n = vec.size();
        if(n == 1)
            return 0;
        vector<int> sums(n + 1, 0);
        for(int i = 1; i <=n ; ++i)
            sums[i] = sums[i - 1] + vec[i - 1];
        vector<vector<int> > dp(n, vector<int>(n, 0));
        for(int j = 1; j < n; ++j)
            for(int i = j - 1; i >= 0; --i)
            {
                dp[i][j] = sums[j + 1] - sums[i];
                int partition_num = j - i;
                int mx = dp[i][i] + dp[i + 1][j];
                for(int k = 1; k < partition_num; ++k)
                    mx = min(mx, dp[i][i + k] + dp[i + 1 + k][j]);
                dp[i][j] += mx;
            }
        return dp[0][n - 1];
    }
};
