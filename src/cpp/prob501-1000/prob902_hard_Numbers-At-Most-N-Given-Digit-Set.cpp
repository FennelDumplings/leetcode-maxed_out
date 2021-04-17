// prob902: Numbers At Most N Given Digit Set

/*
 * We have a sorted set of digits D, a non-empty subset of {'1','2','3','4','5','6','7','8','9'}.  (Note that '0' is not included.)
 * Now, we write numbers using these digits, using each digit as many times as we want.  For example, if D = {'1','3','5'},
 * we may write numbers such as '13', '551', '1351315'.
 * Return the number of positive integers that can be written (using the digits of D) that are less than or equal to N.
 */

/*
 * Example 1:
 * Input: D = ["1","3","5","7"], N = 100
 * Output: 20
 * Explanation:
 * The 20 numbers that can be written are:
 * 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
 * Example 2:
 * Input: D = ["1","4","9"], N = 1000000000
 * Output: 29523
 * Explanation:
 * We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
 * 81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
 * 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
 * In total, this is 29523 integers that can be written using the digits of D.
 */

/*
 * Note:
 * D is a subset of digits '1'-'9' in sorted order.
 * 1 <= N <= 10^9
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        int d = D.size();
        unordered_set<char> setting;
        for(string c: D) setting.insert(c[0]);
        vector<int> lessthan(10, 0); // lessthan[i]: D 中小于 i 的数字的个数, 1 <= i <= 9
        vector<bool> equal(10, false); // equal[i]: i 是否在 D 中, 1 <= i <= 9
        for(int i = 1; i <= 9; ++i)
            if(setting.find('0' + i) != setting.end())
                equal[i] = true;
        for(int i = 2; i <= 9; ++i)
        {
            lessthan[i] = lessthan[i - 1];
            if(equal[i - 1])
                ++lessthan[i];
        }
        vector<int> digits = _num_digit(N);
        int n = digits.size();
        int result = _check(n, d, digits, lessthan, equal);
        for(int i = 1; i <= n - 1; ++i)
            result += pow(d, i);
        return result;
    }

private:
    int _check(int k, int d, vector<int>& digits, vector<int>& lessthan, vector<bool>& equal)
    {
        // k 位数, 且小于等于 N 的前 k 位的选法
        if(k < 1) return 1;
        int result = 0;
        int cur = digits[k - 1];
        result += pow(d, k - 1) * lessthan[cur];
        if(equal[cur])
            result += _check(k - 1, d, digits, lessthan, equal);
        return result;
    }

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


// 数位 DP 模板写法

class Solution_2
{
public:
    int atMostNGivenDigitSet(vector<string>& D, int N)
    {
        set<int> num_set;
        for(const string &s: D)
            num_set.insert(s[0] - '0');

        vector<int> digits;
        while(N)
        {
            digits.push_back(N % 10);
            N /= 10;
        }

        vector<vector<int>> dp(digits.size(), vector<int>(2, -1));
        int n = digits.size();
        int ans = getdp(n - 1, 1, digits, num_set, dp);
        for(int i = 1; i < n; ++i)
            ans += getdp(i - 1, 0, digits, num_set, dp);
        return ans;
    }

private:
    int getdp(int pos, int lim, const vector<int>& digits, const set<int>& num_set, vector<vector<int>>& dp)
    {
        if(pos == -1) return 1;
        if(dp[pos][lim] != -1)
            return dp[pos][lim];
        dp[pos][lim] = 0;
        int up = lim ? digits[pos] : 9; // 当前要枚举到的上界
        for(int i: num_set) // 枚举当前位所有可能数字
        {
            if(i > up)
                break;
            dp[pos][lim] += getdp(pos - 1, lim && i == up, digits, num_set, dp); // 本位被限制且选顶到上界的数字,下一位才被限制
        }
        return dp[pos][lim];
    }
};


// 带前导 0 的数位 dp
class Solution_3
{
public:
    int atMostNGivenDigitSet(vector<string>& D, int N)
    {
        set<int> num_set;
        for(const string &s: D)
            num_set.insert(s[0] - '0');

        vector<int> digits;
        while(N)
        {
            digits.push_back(N % 10);
            N /= 10;
        }

        vector<int> dp(digits.size(), -1);
        int n = digits.size();
        int ans = getdp(n - 1, 1, 1, digits, num_set, dp);
        return ans;
    }

private:
    int getdp(int pos, int lim, int zero, const vector<int>& digits, const set<int>& num_set, vector<int>& dp)
    {
        if(pos == -1) return !zero; // 如果是一直前导零直到 -1
        if(dp[pos] != -1 && !zero && !lim)
            return dp[pos];
        int ans = 0;
        int up = lim ? digits[pos] : 9; // 当前要枚举到的上界
        if(zero)
            ans += getdp(pos -1, 0, 1, digits, num_set, dp);
        for(int i: num_set) // 枚举当前位所有可能数字
        {
            if(i > up)
                break;
            ans += getdp(pos - 1, lim && i == up, 0, digits, num_set, dp); // 本位被限制且选顶到上界的数字,下一位才被限制
        }
        if(!lim && !zero)
            dp[pos] = ans;
        return ans;
    }
};


// 重写数位 DP
class Solution_4
{
public:
    int atMostNGivenDigitSet(vector<string>& D, int N)
    {
        set<int> num_set;
        for(const string &s: D)
            num_set.insert(s[0] - '0');
        // [1, N]
        vector<int> digits;
        while(N)
        {
            digits.push_back(N % 10);
            N /= 10;
        }
        int m = digits.size();
        vector<int> dp(m, -1);
        int ans = getdp(m - 1, 1, 1, digits, dp, num_set);
        return ans;
    }

private:
    int getdp(int pos, int lim, int zero, const vector<int>& digits, vector<int>& dp, const set<int>& num_set)
    {
        if(pos == -1) return !zero;
        if(!lim && !zero && dp[pos] != -1)
            return dp[pos];
        int ans = 0;
        if(zero)
            ans += getdp(pos - 1, 0, 1, digits, dp, num_set);
        int up = lim ? digits[pos] : 9;
        for(int i: num_set)
        {
            if(i > up)
                break;
            if(zero && i == 0) continue;
            ans += getdp(pos - 1, lim && i == up, 0, digits, dp, num_set);
        }
        if(!zero && !lim) dp[pos] = ans;
        return ans;
    }
};
