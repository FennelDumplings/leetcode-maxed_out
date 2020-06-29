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

// 数位 DP 模板
class Solution_2 {
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        vector<int> digits;
        while(n)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
        int m = digits.size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(m, vector<int>(2, -1)));
        return getdp(m - 1, 1, 0, digits, dp);
    }

private:
    int getdp(int pos, int lim, int cnt, const vector<int>& digits, vector<vector<vector<int>>>& dp)
    {
        if(pos == -1) return cnt;
        int &ans = dp[pos][cnt][lim];
        if(ans != -1) return ans;
        ans = 0;
        int up = lim ? digits[pos] : 9;
        for(int i = 0; i <= up; ++i)
        {
            ans += getdp(pos - 1, lim && (i == up), cnt + (i == 1), digits, dp);
        }
        return ans;
    }
};
