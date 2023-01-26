// prob1406: one Game III

/*
 * https://leetcode-cn.com/problems/stone-game-iii/
 */

#include <vector>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int sum = 0;
        for(int i: stoneValue) sum += i;
        int n = stoneValue.size();
        dp = vector<vector<int>>(2, vector<int>(n + 1, INT_MIN / 2));
        dp[1].assign(n, INT_MAX / 2);
        dp[0][n] = 0;
        dp[1][n] = 0;
        int scoreA = solve(stoneValue, 0, 0);
        int scoreB = sum - scoreA;
        if(scoreA == scoreB)
            return "Tie";
        else if(scoreA > scoreB)
            return "Alice";
        else
            return "Bob";
    }

private:
    vector<vector<int>> dp;

    int solve(const vector<int>& s, int i, int k)
    {
        if(dp[k][i] != INT_MIN / 2 && dp[k][i] != INT_MAX / 2)
            return dp[k][i];
        int sum = 0;
        int n = s.size();
        for(int l = 1; l <= 3 && i + l <= n; ++l)
        {
            int j = i + l;
            sum += s[i + l - 1];
            if(k & 1)
                dp[k][i] = min(dp[k][i], solve(s, j, k ^ 1));
            else
                dp[k][i] = max(dp[k][i], sum + solve(s, j, k ^ 1));
        }
        return dp[k][i];
    }
};
