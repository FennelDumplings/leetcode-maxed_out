// prob279: Perfect Squares

/*
 * Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
 */

/*
 * Example 1:
 * Input: n = 12
 * Output: 3
 * Explanation: 12 = 4 + 4 + 4.
 * Example 2:
 * Input: n = 13
 * Output: 2
 * Explanation: 13 = 4 + 9.
 */

#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// DP
class Solution {
public:
    int numSquares(int n) {
        // n >= 1
        vector<int> dp(n + 1, n);
        dp[0] = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j * j <= i; ++j)
                dp[i] = min(dp[i], dp[i - j * j] + 1);
        return dp[n];
    }
};

// BFS
class Solution_2 {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, n);
        queue<int> q;
        dp[0] = 0;
        q.push(0);
        while(!q.empty())
        {
            int s = q.front();
            if(s == n)
                break;
            q.pop();
            for(int i = 1; s + i * i <= n; ++i)
            {
                if(dp[s + i * i] > dp[s] + 1)
                {
                    dp[s + i * i] = dp[s] + 1;
                    q.push(s + i * i);
                }
            }
        }
        return dp[n];
    }
};

// 数学
// 拉格朗日四平方和定理
// 勒让德三平方和定理
class Solution_3 {
public:
    int numSquares(int n) {
        if ((int)sqrt(n) * (int)sqrt(n) == n)
            return 1;
        int t = n;
        while ((t & 3) == 0) t >>= 2;
        if (((t - 7) & 7) == 0)
            return 4;

        for (int i = 1; i * i <= n; i++)
            if ((int)(sqrt(n - i * i)) * (int)(sqrt(n - i * i)) == n - i * i)
                return 2;

        return 3;
    }
};
