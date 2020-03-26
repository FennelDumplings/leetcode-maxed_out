//  prob233: Number of Digit One

/*
 * Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
 */

/*
 * Example:
 * Input: 13
 * Output: 6
 * Explanation: Digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 数位DP
// 从高位到低位统计小于 n 的答案(通法)
class Solution {
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        vector<int> nums = _num_digit(n);
        int L = nums.size();
        vector<int> dp(L + 1, 0), pow(L + 1, 0);
        dp[0] = 0;
        pow[0] = 1;
        for(int i = 1; i <= L; i++)
        {
            dp[i] = dp[i - 1] * 10 + pow[i - 1];
            pow[i] = pow[i - 1] * 10;
        }

        // ones: N 本身含有的1的个数, 从高位向低位枚举过程中记录高位1
        int ans = 0, ones = 0;
        for(int i = L - 1; i >= 0; i--)
        {
            ans += ones * (nums[i] * pow[i]);
            if (nums[i] == 1) {
                ones++;
                ans += dp[i];
            }
            else if (nums[i] != 0)
                ans += pow[i] + dp[i] * nums[i];
        }
        return ans + ones;
    }

private:
    vector<int> _num_digit(int N)
    {
        vector<int> result;
        while(N)
        {
            result.push_back(N % 10);
            N /= 10;
        }
        return result;
    }
};
