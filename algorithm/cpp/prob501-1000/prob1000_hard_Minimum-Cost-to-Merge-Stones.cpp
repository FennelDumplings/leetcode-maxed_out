// prob1000: Minimum Cost to Merge Stones

/*
 * There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.
 * A move consists of merging exactly K consecutive piles into one pile,
 * and the cost of this move is equal to the total number of stones in these K piles.
 * Find the minimum cost to merge all piles of stones into one pile.  If it is impossible, return -1
 */

/*
 * Note:
 * 1 <= stones.length <= 30
 * 2 <= K <= 30
 * 1 <= stones[i] <= 100
 */

#include <vector>
#include <climits>

using namespace std;

// dp[i][j][k] := 区间 [i..j] 上, 合并为 k 堆的最小成本
// 初始化：dp[i][i][1] = 0
// 转移: dp[i][j][k] =
//       k = 1 时 dp[i][j][K] + sum(A[i..j])
//  2 <= k <= K 时 min(dp[i][m][1] + dp[m + 1][j][k - 1])
//  分割点m,左边合并1堆，右边合并k-1堆，一共k堆, 找到使得结果最小的 m
//  答案 dp[0][n - 1][1]
//  k: 2 -> K -> 1
//  i: 0
//  j:
class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        if(stones.empty() || K < 2) return -1;
        int n = stones.size();
        if(n == 1) return 0;
        if((n - 1) % (K - 1) != 0) return -1;

        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + stones[i - 1];

        // 初始化为 INT_MAX, 因为绝大多数情况是没有解的
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(n, vector<int>(K + 1, INT_MAX)));
        for(int i = 0; i < n; ++i)
            dp[i][i][1] = 0;

        for(int len = 2; len <= n; ++len) // 枚举子问题的规模
            for(int i = 0; i <= n - len; ++i)
            {
                // 自底向上构建
                int j = i + len - 1;
                for(int k = 2; k <= K; ++k)
                    for(int m = i; m < j; ++m)
                        if(dp[m + 1][j][k - 1] < INT_MAX && dp[i][m][1] < INT_MAX)
                            dp[i][j][k] = min(dp[i][j][k], dp[i][m][1] + dp[m + 1][j][k - 1]);
                if(dp[i][j][K] < INT_MAX) // 判断 [i..j] 分为 K 堆有没有解
                    dp[i][j][1] = dp[i][j][K] + (sums[j + 1] - sums[i]);
            }
        return dp[0][n - 1][1];
    }
};

class Solution_optim1 {
public:
    int mergeStones(vector<int>& stones, int K) {
        if(stones.empty() || K < 2) return -1;
        int n = stones.size();
        if(n == 1) return 0;
        if((n - 1) % (K - 1) != 0) return -1;

        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + stones[i - 1];

        vector<vector<vector<int> > > dp(n, vector<vector<int> >(n, vector<int>(K + 1, INT_MAX)));
        for(int i = 0; i < n; ++i)
            dp[i][i][1] = 0;

        for(int len = 2; len <= n; ++len)
            for(int i = 0; i <= n - len; ++i)
            {
                int j = i + len - 1;
                for(int k = 2; k <= K; ++k)
                    for(int m = i; m < j; m += (K - 1)) // 只改此一处
                        if(dp[m + 1][j][k - 1] < INT_MAX && dp[i][m][1] < INT_MAX)
                            dp[i][j][k] = min(dp[i][j][k], dp[i][m][1] + dp[m + 1][j][k - 1]);
                if(dp[i][j][K] < INT_MAX)
                    dp[i][j][1] = dp[i][j][K] + (sums[j + 1] - sums[i]);
            }
        return dp[0][n - 1][1];
    }
};

class Solution_optim2 {
public:
    int mergeStones(vector<int>& stones, int K) {
        if(stones.empty() || K < 2) return -1;
        int n = stones.size();
        if(n == 1) return 0;
        if((n - 1) % (K - 1) != 0) return -1;

        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + stones[i - 1];

        vector<vector<int> > dp(n, vector<int>(n, INT_MAX));
        for(int i = 0; i < n; ++i)
            dp[i][i] = 0;

        for(int len = 2; len <= n; ++len)
            for(int i = 0; i <= n - len; ++i)
            {
                int j = i + len - 1;
                for(int m = i; m < j; m += (K - 1)) // 与优化1相同
                    if(dp[m + 1][j] < INT_MAX && dp[i][m] < INT_MAX)
                        dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
                        // dp[i][j] := [i..j] 合并为 (j-i)%(K-1)+1 堆
                if((len - 1) % (K - 1) == 0) // 判断子问题可解
                    dp[i][j] += (sums[j + 1] - sums[i]);
            }
        return dp[0][n - 1];
    }
};
