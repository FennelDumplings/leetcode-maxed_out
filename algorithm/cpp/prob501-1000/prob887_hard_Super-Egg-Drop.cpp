// prob887: Super Egg Drop

/*
 * You are given K eggs, and you have access to a building with N floors from 1 to N.
 * Each egg is identical in function, and if an egg breaks, you cannot drop it again.
 * You know that there exists a floor F with 0 <= F <= N such that any egg dropped at a floor higher than F will break, and any egg dropped at or below floor F will not break.
 * Each move, you may take an egg (if you have an unbroken one) and drop it from any floor X (with 1 <= X <= N).
 * Your goal is to know with certainty what the value of F is.
 * What is the minimum number of moves that you need to know with certainty what F is, regardless of the initial value of F?
 */

/*
 * Example 1:
 * Input: K = 1, N = 2
 * Output: 2
 * Example 2:
 * Input: K = 2, N = 6
 * Output: 3
 * Example 3:
 * Input: K = 3, N = 14
 * Output: 4
 */

#include <vector>
#include <climits>

using namespace std;

// 朴素 DP
// 二维线性 dp O(KN^2) TLE
class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int> > dp(K + 1, vector<int>(N + 1, INT_MAX));
        for(int n = 0; n <= N; ++n)
        {
            dp[0][n] = 0;
            dp[1][n] = n;
        }
        for(int k = 0; k <= K; ++k)
        {
            dp[k][0] = 0;
            dp[k][1] = 1;
        }
        for(int i = 2; i <= K; ++i)
            for(int k = 2; k <= N; ++k)
            {
                for(int t = 1; t <= k; ++t)
                    dp[i][k] = min(dp[i][k], max(dp[i - 1][t - 1], dp[i][k - t]) + 1);
            }
        return dp[K][i];
    }
};

// 朴素 DP 的加二分的优化，O(KNlogN) 700ms
// 空间 O(KN)
class Solution_optim1 {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int> > dp(K + 1, vector<int>(N + 1, INT_MAX));
        for(int n = 0; n <= N; ++n)
        {
            dp[0][n] = 0;
            dp[1][n] = n;
        }
        for(int k = 0; k <= K; ++k)
        {
            dp[k][0] = 0;
            dp[k][1] = 1;
        }
        for(int k = 2; k <= K; ++k)
            for(int n = 2; n <= N; ++n)
            {
                /**********************************
                for(int i = 1; i <= n; ++i)
                    dp[k][n] = min(dp[k][n], max(dp[k - 1][i - 1], dp[k][n - i]) + 1);
                **********************************/
                // 二分地从 [1..n] 找 i
                int left = 1, right = n, mid = 0;
                while(left <= right)
                {
                    mid = left + (right - left) / 2;
                    int T1 = dp[k - 1][mid - 1];
                    int T2 = dp[k][n - mid];
                    dp[k][n] = min(dp[k][n], max(T1, T2) + 1);
                    if(T1 > T2) // mid 大了
                        right = mid - 1;
                    else if(T1 < T2)// mid 小了
                        left = mid + 1;
                    else // 剪枝，增加这一步之后 700ms -> 200ms
                        break;
                }
            }
        return dp[K][N];
    }
};

// 对加二分优化的 dp 进一步优化
// 时间 O(KN) 空间O(N)
// 100ms
class Solution_optim2 {
public:
    int superEggDrop(int K, int N) {
        vector<int> dp(N + 1, 0);
        // only one egg situation
        for (int i = 0; i <= N; ++i)
            dp[i] = i;

        // two and more eggs
        for (int k = 2; k <= K; ++k) {
            vector<int> dp2(N + 1, 0);
            int x = 1; // start from floor 1, 遍历找最小值点 Xa
            for (int n = 1; n <= N; ++n) {
                // start to calculate from bottom
                // Notice max(dp[x-1], dp2[n-x]) > max(dp[x], dp2[n-x-1])
                // is simply max(T1(x-1), T2(x-1)) > max(T1(x), T2(x)).
                while (x < n && max(dp[x - 1], dp2[n - x]) > max(dp[x], dp2[n - x - 1]))
                    x++;

                // The final answer happens at this x.
                dp2[n] = 1 + max(dp[x - 1], dp2[n - x]);
            }
            // for循环中，dp 代表是上一次循环解出来的最小值，也就是比当前楼层低一层的情况下的最优解
            dp = dp2; // 当前k的结果滚动进上一轮的结果
        }
        return dp[N];
    }
};

// dp[k][m] k个鸡蛋m步，最多可测多少层，高于这个数一定测不出来
// 时间O(KlogN), 空间O(KN)
// dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1
//            未来可能测出的数量 + 已经测出的数量 + 当前层
class Solution_optim3 {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int> > dp(K + 1, vector<int>(N + 1, 0));
        for (int m = 1; m <= N; m++) {
            dp[0][m] = 0; // zero egg
            for (int k = 1; k <= K; k++) {
                dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1;
                if (dp[k][m] >= N) {
                    return m;
                }
            }
        }
        return N;
    }
};

// optim3 的空间优化(滚动数组)
// 时间 O(KlogN) 空间O(K)
// 4ms
class Solution_optim4 {
public:
    int superEggDrop(int K, int N) {
        vector<int> dp(K + 1, 0);
        int m;
        for (m = 0; dp[K] < N; m++)
            for (int k = K; k > 0; --k)
                dp[k] += dp[k - 1] + 1;
        return m;
    }
};

// 数学法，本质类似于 optim3 -- 函数定义为可测层数
// 空间 O(1), 时间 O(KlogN)
// 4ms
class Solution_optim5 {
public:
    int superEggDrop(int K, int N) {
        int lo = 1, hi = N;
        while (lo < hi) {
            int mi = (lo + hi) / 2;
            // 可测层数
            if (f(mi, K, N) < N)
                lo = mi + 1;
            else
                hi = mi;
        }
        return lo;
    }

private:
    int f(int x, int K, int N) {
        int ans = 0, r = 1;
        for (int i = 1; i <= K; ++i) {
            r *= x - i + 1;
            r /= i;
            ans += r;
            if (ans >= N) break;
        }
        return ans;
    }
};

// 数学法另一写法 -- 函数定义为可测区间数
// 4ms
class Solution_optim6 {
public:
    int superEggDrop(int K, int N)
    {
        int T = 1;    // 测试机会
        // 可测区间数
        while (fun(K, T) < N + 1) T++;
        return T;
    }

private:
    int fun(int K, int T)    // 计算 K 个鸡蛋，扔 T 次，可以覆盖多少个区间
    {
        //if (T == 1) return 2;
        //if (K == 1) return T + 1;
        if (T == 1 || K == 1) return T + 1;    // 上面两句可以合并成这一句

        return fun(K - 1, T - 1) + fun(K, T - 1);
    }
};
