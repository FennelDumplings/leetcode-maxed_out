// prob1302: Number of Paths with Max Score

/*
 * https://leetcode-cn.com/problems/number-of-paths-with-max-score/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        using ll = long long;
        int n = board.size();
        vector<vector<ll>> dp(n, vector<ll>(n, -1));
        dp[0][0] = 0;
        vector<vector<int>> cnts(n, vector<int>(n, 0));
        cnts[0][0] = 1;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j)
            {
                if(!check(board, i, j))
                    continue;

                int num = 0;
                if(board[i][j] >= '0' && board[i][j] <= '9')
                    num = board[i][j] - '0';

                if(i > 0 && j > 0 && dp[i - 1][j - 1] != -1)
                    dp[i][j] = max(dp[i][j], num + dp[i - 1][j - 1]);
                if(i > 0 && dp[i - 1][j] != -1)
                    dp[i][j] = max(dp[i][j], num + dp[i - 1][j]);
                if(j > 0 && dp[i][j - 1] != -1)
                    dp[i][j] = max(dp[i][j], num + dp[i][j - 1]);

                if(i > 0 && j > 0 && dp[i - 1][j - 1] != -1)
                    if(dp[i][j] == num + dp[i - 1][j - 1])
                        cnts[i][j] = (cnts[i][j] + (ll)cnts[i - 1][j - 1]) % MOD;
                if(i > 0 && dp[i - 1][j] != -1)
                    if(dp[i][j] == num + dp[i - 1][j])
                        cnts[i][j] = (cnts[i][j] + (ll)cnts[i - 1][j]) % MOD;
                if(j > 0 && dp[i][j - 1] != -1)
                    if(dp[i][j] == num + dp[i][j - 1])
                        cnts[i][j] = (cnts[i][j] + (ll)cnts[i][j - 1]) % MOD;
            }
        }
        if(dp[n - 1][n - 1] == -1)
            return {0, 0};
        return {(int)(dp[n - 1][n - 1] % MOD), cnts[n - 1][n - 1]};
    }

private:
    bool check(const vector<string>& board, int i, int j)
    {
        return board[i][j] != 'X';
    }
};

