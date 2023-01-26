// prob518: Coin Change 2

/*
 *
 * You are given coins of different denominations and a total amount of money.
 * Write a function to compute the number of combinations that make up that amount.
 * You may assume that you have infinite number of each kind of coin.
 */

/*
 * Example 1:
 * Input: amount = 5, coins = [1, 2, 5]
 * Output: 4
 * Explanation: there are four ways to make up the amount:
 * 5=5
 * 5=2+2+1
 * 5=2+1+1+1
 * 5=1+1+1+1+1
 * Example 2:
 * Input: amount = 3, coins = [2]
 * Output: 0
 * Explanation: the amount of 3 cannot be made up just with coins of 2.
 * Example 3:
 * Input: amount = 10, coins = [10]
 * Output: 1
 */

/*
 * Note:
 * You can assume that
 * 0 <= amount <= 5000
 * 1 <= coin <= 5000
 * the number of coins is less than 500
 * the answer is guaranteed to fit into signed 32-bit integer
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // if(amount == 0) return 1;
        int N = coins.size();

        vector<int> dp(amount + 1, INT_MIN);
        dp[0] = 0;
        vector<int> g(amount + 1, 0);
        g[0] = 1;

        for(int i = 0; i < N; ++i)
            for(int j = coins[i]; j <= amount; ++j)
            {
                int s = 0;
                int t = max(dp[j], dp[j - coins[i]]);
                if(dp[j] == t) s += g[j];
                if(dp[j - coins[i]] == t) s += g[j - coins[i]];
                g[j] = s;
                dp[j] = t;
            }
        if(g[amount] == INT_MIN) return 0;
        return g[amount];
    }
};
