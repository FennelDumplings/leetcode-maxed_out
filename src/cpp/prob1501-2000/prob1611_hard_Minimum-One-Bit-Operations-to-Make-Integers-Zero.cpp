// prob1611: Minimum One Bit Operations to Make Integers Zero

/*
 * https://leetcode-cn.com/problems/minimum-one-bit-operations-to-make-integers-zero/
 */

#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

int low_bit(int n)
{
    return n & (-n);
}

int high_bit(int n)
{
    int p = low_bit(n);
    while(p != n)
    {
        n -= p;
        p = low_bit(n);
    }
    return p;
}

class Solution {
public:
    int minimumOneBitOperations(int n) {
        if(n <= 1) return n;
        dp[1] = 1;
        return solve(n);
    }

private:
    unordered_map<int, int> dp;

    int solve(int x)
    {
        if(dp.count(x) != 0)
            return dp[x];

        int highbit = high_bit(x);
        int y = x - highbit;
        if(y == 0)
            return dp[x] = solve(x / 2) * 2 + 1;
        else
            return dp[x] = solve(highbit) - solve(y);
    }
};
