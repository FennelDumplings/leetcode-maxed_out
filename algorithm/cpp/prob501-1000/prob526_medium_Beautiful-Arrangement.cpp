// prob526: Beautiful Arrangement

/*
 * Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is
 * constructed by these N numbers successfully if one of the following is true for the ith position (1 <= i <= N) in this array:
 * The number at the ith position is divisible by i.
 * i is divisible by the number at the ith position.
 *  Now given N, how many beautiful arrangements can you construct?
 */

/*
 * Note:
 * N is a positive integer and will not exceed 15.
 */

/*
 * Example 1:
 * Input: 2
 * Output: 2
 * Explanation:
 * The first beautiful arrangement is [1, 2]:
 * Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).
 * Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).
 * The second beautiful arrangement is [2, 1]:
 * Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).
 * Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
 */

#include <vector>

using namespace std;

// 状态压缩 DP 的写法
class Solution {
public:
    int countArrangement(int N) {
        if(N == 1) return 1;
        vector<int> dp(1 << N, 0);
        dp[0] = 1; // 一个数都没取的时候有 1 种方案
        for(int i = 0; i < (1 << N); ++i)
        {
            int s = 1; // 计算当前的状态
            for(int j = 0; j < N; ++j)
                s += i >> j & 1;
            for(int j = 1; j <= N; ++j)
                if(!(i >> (j - 1) & 1) && (j % s == 0 || s % j == 0))
                {
                    // 判断 j 是否在状态 s 中出现
                    dp[i | 1 << (j - 1)] += dp[i];
                }
        }
        return dp[(1 << N) - 1];
    }
};
