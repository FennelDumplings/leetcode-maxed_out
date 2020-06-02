// prob90: Domino and Tromino Tiling

/*
 * We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.
 * XX  <- domino
 * XX  <- "L" tromino
 * X
 * Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.
 * (In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)
 */

/*
 * Example:
 * Input: 3
 * Output: 5
 * Explanation:
 * The five different ways are listed below, different letters indicates different tiles:
 * XYZ XXZ XYY XXY XYY
 * XYZ YYZ XZZ XYY XXY
 */

/*
 * Note:
 * N  will be in range [1, 1000].
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numTilings(int N) {
        if(N == 1) return 1;
        if(N == 2) return 2;
        vector<int> f(N + 1, 0), g(N + 1, 0);
        f[1] = 1, f[2] = 2;
        g[1] = 1;
        g[2] = 2;
        for(int i = 3; i <= N; ++i)
        {
            f[i] = ((ll)f[i - 1] + (ll)f[i - 2] + 2 * (ll)g[i - 2]) % MOD;
            g[i] = ((ll)g[i - 1] + (ll)f[i - 1]) % MOD;
        }
        return f[N];
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
};
