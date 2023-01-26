// prob837: new 21 Game

/*
 * Alice plays the following game, loosely based on the card game "21".
 * Alice starts with 0 points, and draws numbers while she has less than K points.  During each draw, she gains an integer
 * number of points randomly from the range [1, W], where W is an integer.  Each draw is independent and the outcomes have equal probabilities.
 * Alice stops drawing numbers when she gets K or more points.  What is the probability that she has N or less points?
 */

/*
 * Example 1:
 * Input: N = 10, K = 1, W = 10
 * Output: 1.00000
 * Explanation:  Alice gets a single card, then stops.
 * Example 2:
 * Input: N = 6, K = 1, W = 10
 * Output: 0.60000
 * Explanation:  Alice gets a single card, then stops.
 * In 6 out of W = 10 possibilities, she is at or below N = 6 points.
 * Example 3:
 * Input: N = 21, K = 17, W = 10
 * Output: 0.73278
 */

/*
 * Note:
 * 0 <= K <= N <= 10000
 * 1 <= W <= 10000
 * Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 * The judging time limit has been reduced for this question.
 */

#include <vector>

using namespace std;

// 前缀和维护状态转移
class Solution {
public:
    double new21Game(int N, int K, int W) {
        if(K == 0) return 1.0; // 1 个数也不会抽
        vector<double> dp(N + 1, 0);
        vector<double> sums(N + 2, 0);
        dp[0] = 1;
        sums[0] = 0, sums[1] = 1;
        for(int i = 1; i <= N; ++i)
        {
            // 枚举哪些值可以得到 i;
            // j 属于 [i - W, i - 1] 且 j >= 0 && j < K
            dp[i] = (sums[min(i, K)] - sums[max(i - W, 0)]) / W;
            sums[i + 1] = sums[i] + dp[i];
        }
        return sums[N + 1] - sums[K];
    }
};

// dp
// 枚举状态转移 TLE
class Solution_2 {
public:
    double new21Game(int N, int K, int W) {
        if(K == 0) return 1.0; // 1 个数也不会抽
        vector<double> dp(N + 1, 0);
        vector<double> sums(N + 2, 0);
        dp[0] = 1;
        sums[0] = 0, sums[1] = 1;
        for(int i = 1; i <= N; ++i)
        {
            // 枚举哪些值可以得到 i;
            // j 属于 [i - W, i - 1] 且 j >= 0 && j < K
            for(int j = max(i - W, 0); j < min(i, K); ++j)
               dp[i] = dp[i] + dp[j] / W;
            sums[i + 1] = sums[i] + dp[i];
        }
        return sums[N + 1] - sums[K];
    }
};
