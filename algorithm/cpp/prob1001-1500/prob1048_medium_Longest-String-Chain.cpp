// prob1048: Longest String Chain

/*
 * https://leetcode-cn.com/problems/longest-string-chain/
 */

#include <vector>
#include <string>
#include <queue>

using namespace std;

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        vector<vector<int> > g(n);
        vector<int> indegrees(n);
        for(int i = 0; i < (n - 1); ++i)
            for(int j = i + 1; j < n; ++j)
            {
                int li = words[i].size(), lj = words[j].size();
                if(li + 1 == lj && check(words[i], words[j]))
                {
                    // i 是 j 前驱
                    g[i].push_back(j);
                    ++indegrees[j];
                }
                if(lj + 1 == li && check(words[j], words[i]))
                {
                    // j 是 i 前驱
                    g[j].push_back(i);
                    ++indegrees[i];
                }
            }
        vector<int> dp(n, -1); // dp[i] := 以 i 为起点的最长链
        for(int i = 0; i < n; ++i)
            if(g[i].empty())
                dp[i] = 1;
        int ans = 0;
        for(int i = 0; i < n; ++i)
            if(indegrees[i] == 0)
            {
                ans = max(ans, solve(i, g, dp));
            }
        return ans;
    }

private:
    int solve(int i, const vector<vector<int> >& g, vector<int>& dp)
    {
        if(dp[i] != -1)
            return dp[i];

        dp[i] = 0;
        for(int son: g[i])
            dp[i] = max(dp[i], solve(son, g, dp));
        ++dp[i];
        return dp[i];
    }

    bool check(const string& s1, const string& s2)
    {
        // 调用方保证 l1 + 1 == l2
        int l1 = s1.size();
        int i1 = 0, i2 = 0;
        int cnt = 1;
        while(i1 < l1)
        {
            if(s1[i1] != s2[i2]) // 需要插入 s2[i2]
            {
                --cnt;
                if(cnt < 0) return false;
            }
            else
                ++i1;
            ++i2;
        }
        return true;
    }
};
