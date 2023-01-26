// prob1639: Number of Ways to Form a Target String Given a Dictionary

/*
 * https://leetcode-cn.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution_2 {
public:
    int numWays(vector<string>& words, string target) {
        int n = target.size();
        int L = words[0].size();
        mappings.assign(L, unordered_map<int, int>());
        for(const string &s: words)
            for(int j = 0; j < L; ++j)
                ++mappings[j][s[j]];
        dp.assign(n, vector<int>(L, -1));
        return solve(target, 0, 0);
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    vector<unordered_map<int, int>> mappings;
    vector<vector<int>> dp;

    int solve(const string& t, int i, int k)
    {
        int n = t.size(), L = mappings.size();
        if(i == n)
            return 1;
        if(k == L)
            return 0;
        if(dp[i][k] != -1)
            return dp[i][k];

        dp[i][k] = 0;
        for(int j = k; j < L; ++j)
        {
            if(mappings[j].count(t[i]) > 0)
            {
                dp[i][k] = ((ll)dp[i][k] + (ll)mappings[j][t[i]] * solve(t, i + 1, j + 1)) % MOD;
            }
        }
        return dp[i][k];
    }
};


class Solution {
public:
    int numWays(vector<string>& words, string target) {
        int n = target.size();
        int L = words[0].size();
        mappings.assign(L, unordered_map<int, int>());
        for(const string &s: words)
            for(int j = 0; j < L; ++j)
                ++mappings[j][s[j]];
        dp.assign(n, vector<int>(L, -1));
        return solve(target, 0, 0);
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    vector<unordered_map<int, int>> mappings;
    vector<vector<int>> dp;

    int solve(const string& t, int i, int k)
    {
        int n = t.size(), L = mappings.size();
        if(i == n)
            return 1;
        if(k == L)
            return 0;
        if(n - i > L - k)
            return 0;
        if(dp[i][k] != -1)
            return dp[i][k];

        dp[i][k] = solve(t, i, k + 1);
        if(mappings[k].count(t[i]) > 0)
            dp[i][k] = (dp[i][k] + (ll)solve(t, i + 1, k + 1) * mappings[k][t[i]]) % MOD;
        return dp[i][k];
    }
};
