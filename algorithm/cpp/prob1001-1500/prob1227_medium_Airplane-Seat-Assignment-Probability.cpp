// prob1227: Airplane Seat Assignment Probability

/*
 * https://leetcode-cn.com/problems/airplane-seat-assignment-probability/
 */

//dp[i] := i 个人，i 个座位，第 1 个人随机选，后面 i - 1 个人按规则选，第 i 个人选的时候 i 未被占的概率
//Base Case: dp[1] = 1, dp[2] = 0.5
//答案：dp[n]
//
// 转移 dp[i] = 1/i + sum(dp[j]/i), j = 1,2,...,i-1

#include <vector>

using namespace std;

class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        if(n == 1) return 1;
        if(n == 2) return 0.5;
        vector<double> dp(n + 1, 0.0);
        dp[1] = 1.0;
        dp[2] = 0.5;
        for(int i = 3; i <= n; ++i)
        {
            dp[i] = 1 / (double)i;
            for(int j = 2; j < i; ++j)
            {
                dp[i] = dp[i] + dp[j] / i;
            }
        }
        return dp[n];
    }
};
