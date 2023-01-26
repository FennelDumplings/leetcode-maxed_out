// prob322: Coin Change

/*
 * You are given coins of different denominations and a total amount of money amount.
 * Write a function to compute the fewest number of coins that you need to make up that amount.
 * If that amount of money cannot be made up by any combination of the coins, return -1.
 */

/*
 * Example 1:
 * Input: coins = [1, 2, 5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1
 * Example 2:
 * Input: coins = [2], amount = 3
 * Output: -1
 */

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// 负价值
// 转移用 max
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        using ll = long long;
        if(coins.empty()) return 0;

        int N = coins.size();
        vector<int> dp(amount + 1, INT_MIN);
        dp[0] = 0;
        for(int i = 0; i < N; ++i)
            for(int j = coins[i]; j <= amount; ++j)
                dp[j] = max((ll)dp[j], (ll)dp[j - coins[i]] + (-1));
        if(dp[amount] == INT_MIN) return -1;
        return -dp[amount];
    }
};

// 正价值，转移用min
class Solution_2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        using ll = long long;
        if(coins.empty()) return 0;

        int N = coins.size();
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < N; ++i)
            for(int j = coins[i]; j <= amount; ++j)
                dp[j] = min((ll)dp[j], (ll)dp[j - coins[i]] + 1);
        if(dp[amount] == INT_MAX) return -1;
        return dp[amount];
    }
};

class Solution_3 {
public:
    int coinChange(vector<int>& coins, int amount) {
        using ll = long long;
        if(coins.empty()) return 0;

        int N = coins.size();
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < N; ++i)
            for(int j = coins[i]; j <= amount; j += coins[i])
                dp[j] = min((ll)dp[j], (ll)dp[j - coins[i]] + 1);
        if(dp[amount] == INT_MAX) return -1;
        return dp[amount];
    }
};

// DFS + 剪枝
class Solution_4 {
public:
    int coinChange(vector<int>& coins, int amount) {
        int ans = INT_MAX;
        sort(coins.begin(), coins.end());
        dfs(coins, coins.size() - 1, amount, 0, ans);
        return ans ==INT_MAX ? -1 : ans;
    }

private:
    void dfs(vector<int>& coins, int index, int amount,int cnt, int& ans)
    {
        if(index < 0)
            return;
        for(int c = amount / coins[index]; c >= 0; c--)
        {
            int na = amount - c * coins[index];
            int ncnt = cnt + c;
            if(na == 0){
                ans = min(ans, ncnt);
                break;//剪枝1
            }
            if(ncnt + 1 >= ans){
                break; //剪枝2
            }
            dfs(coins, index - 1, na, ncnt, ans);
        }
    }
};
