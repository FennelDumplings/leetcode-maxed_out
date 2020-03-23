// prob1025: Divisor Game

/*
 * Alice and Bob take turns playing a game, with Alice starting first.
 * Initially, there is a number N on the chalkboard.  On each player's turn, that player makes a move consisting of:
 * Choosing any x with 0 < x < N and N % x == 0.
 * Replacing the number N on the chalkboard with N - x.
 * Also, if a player cannot make a move, they lose the game.
 * Return True if and only if Alice wins the game, assuming both players play optimally.
 */

/*
 * Example 1:
 * Input: 2
 * Output: true
 * Explanation: Alice chooses 1, and Bob has no more moves.
 * Example 2:
 * Input: 3
 * Output: false
 * Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
 */

/*
 * Note:
 * 1 <= N <= 1000
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool divisorGame(int N) {
        if(N == 1) return false;
        vector<bool> dp(N + 1, false);
        vector<int> factors;
        for(int i = 2; i <= N; ++i)
        {
            _get_factors(i, factors);
            for(int factor: factors)
            {
                if(!dp[i - factor])
                    dp[i] = true;
            }
        }
        return dp[N];
    }

private:
    void _get_factors(int N, vector<int>& factors)
    {
        factors.clear();
        for(int i = 1; i * 2 <= N; ++i)
        {
            if(N % i == 0)
                factors.push_back(i);
        }
    }
};
