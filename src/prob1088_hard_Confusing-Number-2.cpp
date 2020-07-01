// prob1088: Confusing Number II

/*
 * We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid.
 * A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.(Note that the rotated number can be greater than the original number.)
 * Given a positive integer N, return the number of confusing numbers between 1 and N inclusive.
 */

/*
 * Example 1:
 * Input: 20
 * Output: 6
 * Explanation:
 * The confusing numbers are [6,9,10,16,18,19].
 * 6 converts to 9.
 * 9 converts to 6.
 * 10 converts to 01 which is just 1.
 * 16 converts to 91.
 * 18 converts to 81.
 * 19 converts to 61.
 * Example 2:
 * Input: 100
 * Output: 19
 * Explanation:
 * The confusing numbers are [6,9,10,16,18,19,60,61,66,68,80,81,86,89,90,91,98,99,1
 */

/*
 * Note:
 * 1 <= N <= 10^9
 */

#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int confusingNumberII(int N) {
        // lc248
        mapping[0] = 0;
        mapping[1] = 1;
        mapping[8] = 8;
        mapping[6] = 9;
        mapping[9] = 6;
        int positive_cnt = solve(to_string(N)) - 1 + check(to_string(N));
        positive_cnt = max(positive_cnt, 0);

        // lc902
        set<int> num_set({0, 1, 6, 8, 9});
        vector<int> digits;
        while(N)
        {
            digits.push_back(N % 10);
            N /= 10;
        }
        int m = digits.size();
        vector<int> dp(m, -1);
        int cnt = getcnt(m - 1, 1, 1, digits, dp, num_set);
        return cnt - positive_cnt;
    }
private:
    unordered_map<int, int> mapping;

    // lc902
    int getcnt(int pos, int lim, int zero, const vector<int>& digits, vector<int>& dp, const set<int>& num_set)
    {
        if(pos == -1) return !zero;
        if(!lim && !zero && dp[pos] != -1)
            return dp[pos];
        int ans = 0;
        if(zero)
            ans += getcnt(pos - 1, 0, 1, digits, dp, num_set);
        int up = lim ? digits[pos] : 9;
        for(int i: num_set)
        {
            if(i > up)
                break;
            if(zero && i == 0) continue;
            ans += getcnt(pos - 1, lim && i == up, 0, digits, dp, num_set);
        }
        if(!zero && !lim) dp[pos] = ans;
        return ans;
    }

    // lc 248
    int getdp(int pos, int lim, int odd, int fi, const vector<int>& digits, vector<vector<vector<int>>>& dp)
    {
        // fi 的意义与前导零类似
        if(pos == -1) return 1;
        int ans = dp[pos][lim][odd];
        if(!fi && ans != -1) return ans;
        ans = 0;
        int up = lim ? digits[pos] : 9;
        for(int i: {0, 1, 6, 8, 9})
        {
            if(i > up)
                break;
            if(fi && i == 0) // 都枚举严格等于长度的 , 最高位严格不是 0
                continue;
            if(odd && pos == 0 && (i == 6 || i == 9)) // 奇数长的中间位置只能是 0, 1, 8
                continue;
            ans += getdp(pos - 1, lim && i == up, odd, 0, digits, dp);
        }
        if(!fi)
            dp[pos][lim][odd] = ans;
        return ans;
    }

    int solve(const string& s)
    {
        if(s == "0") return 0;
        int n = s.size();
        vector<int> digits;
        for(int i = 0; i < (n + 1) / 2; ++i) // 仅枚举前一半
        {
            digits.push_back(s[i] - '0');
        }
        reverse(digits.begin(), digits.end());
        int m = digits.size();
        for(int i = 0; i < m; ++i)
        {
            if(digits[i] > 0)
            {
                --digits[i];
                break; // N = 35956 的例子中, 将前半部分变为 358
            }
            digits[i] = 9;
        }
        int ans = 0;
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(2, vector<int>(2, -1)));
        if(digits.back() != 0) // 100000, 此时取一半, 前一半未顶上界时, 99 , 位数少了
            ans += getdp(m - 1, 1, n & 1, 1, digits, dp);
        for(int i = n - 1; i >= 1; --i) // 所有比当前串短的贡献都算一下
            ans += getdp((i + 1) / 2 - 1, 0, i & 1, 1, digits, dp);
        return ans + 1; // "0"
    }

    bool check(const string& s)
    {
        // 处理前缀都顶到上界的情况
        // 看后半部分对称过去之后是否合法
        int n = s.size();
        string ns;
        for(int i = 0; i < (n + 1) / 2; ++i)
        {
            if(!mapping.count(s[i] - '0'))
                return false;
        }
        if((n & 1) && (s[(n - 1) / 2] == '6' || s[(n - 1) / 2] == '9'))
            return false;
        for(int i = (n + 1) / 2; i < n; ++i)
        {
            int a = s[i] - '0';
            int b = mapping[s[n - i - 1] - '0'];
            if(a != b)
                return a > b; // 前面一半与限制一样，对称过去的部分只要比限制小就是能取到的
        }
        return true;
    }
};
