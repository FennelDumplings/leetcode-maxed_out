// prob292: Nim Game

/*
 * You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of
 * you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner.
 * You will take the first turn to remove the stones.
 * Both of you are very clever and have optimal strategies for the game. Write a function to determine whether
 * you can win the game given the number of stones in the heap.
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool canWinNim(int n) {
        return n % 4 != 0;
        if(n == 1 || n == 2 || n == 3) return true;
        if(n == 4) return false;
        vector<bool> dp(n + 1, false);
        dp[1] = true;
        dp[2] = true;
        dp[3] = true;
        for(int i = 5; i <= n; ++i)
            dp[i] = (!dp[i - 1] || !dp[i - 2] || !dp[i - 3]);
        return dp[n];
    }
};
