// prob1553: Minimum Number of Days to Eat N Oranges

/*
 * https://leetcode-cn.com/problems/minimum-number-of-days-to-eat-n-oranges/
 */

#include <unordered_map>

using namespace std;

class Solution {
public:
    int minDays(int n) {
        dp[1] = 1;
        return solve(n);
    }

private:
    unordered_map<int, int> dp;

    int solve(int i)
    {
        if(dp.count(i) > 0)
            return dp[i];
        if(i % 3 == 0 && i % 2 == 0)
            dp[i] = min(solve(i / 2), solve(i / 3)) + 1;
        else if(i % 3 == 0)
            dp[i] = min(solve(i / 3), solve(i - 1)) + 1;
        else if(i % 2 == 0)
            dp[i] = min(solve(i / 2), solve(i - 1)) + 1;
        else
            dp[i] = solve(i - 1) + 1;
        return dp[i];
    }
};
