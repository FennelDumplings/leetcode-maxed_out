// prob646: Maximum Length of Pair Chain

/*
 * https://leetcode-cn.com/problems/maximum-length-of-pair-chain/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Cmp
{
    bool operator()(const vector<int>& r1, const vector<int>& r2) const
    {
        return r1[0] < r2[0];
    }
};

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), Cmp());
        int n = pairs.size();
        vector<int> lefts(n);
        for(int i = 0; i < n; ++i)
            lefts[i] = pairs[i][0];
        vector<int> dp(n);
        dp[n - 1] = 1;
        for(int i = n - 2; i >= 0; --i)
        {
            if(pairs[i][1] >= pairs[i + 1][0])
            {
                dp[i] = dp[i + 1];
                auto it = upper_bound(lefts.begin() + i, lefts.end(), pairs[i][1]);
                int k = it - lefts.begin();
                if(k < n)
                    dp[i] = max(dp[i], 1 + dp[k]);
            }
            else
                dp[i] = 1 + dp[i + 1];
        }
        return dp[0];
    }
};
