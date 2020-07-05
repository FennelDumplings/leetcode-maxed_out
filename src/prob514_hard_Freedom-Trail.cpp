// prob514: Freedom Trail

/*
 * https://leetcode-cn.com/problems/freedom-trail/
 */

#include <vector>
#include <string>
#include <climits>

using namespace std;

// 24ms
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size();
        vector<vector<int>> mapping(26); // ring 中 r -> idxs
        for(int i = 0; i < n; ++i)
        {
            mapping[ring[i] - 'a'].push_back(i);
        }

        // dp[i][j] := 当前在 key[i], ring[j] 的最少步数
        int m = key.size();
        vector<vector<int>> dp(n, vector<int>(m + 1, -1));
        for(int i = 0; i < n; ++i)
            dp[i][m] = 0;
        return solve(0, 0, key, ring, mapping, dp);
    }

private:
    int solve(int i, int j, const string& key, const string& ring, const vector<vector<int>>& mapping, vector<vector<int>>& dp)
    {
        if(dp[i][j] != -1) return dp[i][j];
        int n = ring.size();
        // 当前在 ring[i], 输入 key[j..m-1] 所需步数
        int ans = INT_MAX;
        for(int nxt: mapping[key[j] - 'a'])
        {
            int step = min((n + i - nxt) % n, (n + nxt - i) % n);
            ans = min(ans, step + 1 + solve(nxt, j + 1, key, ring, mapping, dp));
        }
        return dp[i][j] = ans;
    }
};

// 268 ms
// fsm 有点多余
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        // k = fsm[i][ch] :=  当前在 ring[i] 位置，到达最近 ch 的步数(不含含确认), nxt = i +- k
        int n = ring.size();
        vector<vector<vector<int>>> fsm(n, vector<vector<int>>(26));
        for(int i = 0; i < n; ++i)
        {
            fsm[i][ring[i] - 'a'].push_back(0);
            // i + 1..i+n/2
            for(int k = 1; k <= n /2; ++k)
            {
                fsm[i][ring[(i + k) % n] - 'a'].push_back(k);
            }
            // i - 1..i-(n-1)/2
            for(int k = 1; k <= (n - 1) / 2; ++k)
            {
                fsm[i][ring[(n + i - k) % n] - 'a'].push_back(k);
            }
        }

        // dp[i][j] := 当前在 key[i], ring[j] 的最少步数
        int m = key.size();
        vector<vector<int>> dp(n, vector<int>(m + 1, -1));
        for(int i = 0; i < n; ++i)
            dp[i][m] = 0;
        return solve(0, 0, key, ring, fsm, dp);
    }

private:
    int solve(int i, int j, const string& key, const string& ring, const vector<vector<vector<int>>>& fsm, vector<vector<int>>& dp)
    {
        if(dp[i][j] != -1) return dp[i][j];
        int n = ring.size();
        // 当前在 ring[i], 输入 key[j..m-1] 所需步数
        int ans = INT_MAX;
        for(int step: fsm[i][key[j] - 'a'])
        {
            if(ring[(i + step) % n] == key[j])
            {
                ans = min(ans, step + 1 + solve((i + step) % n, j + 1, key, ring, fsm, dp));
            }
            if(ring[(n + i - step) % n] == key[j])
            {
                ans = min(ans, step + 1 + solve((n + i - step) % n, j + 1, key, ring, fsm, dp));
            }
        }
        return dp[i][j] = ans;
    }
};
