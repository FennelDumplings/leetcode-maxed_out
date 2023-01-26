// prob248: Strobogrammatic Number III

/*
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 * Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.
 */

/*
 * Example:
 * Input: low = "50", high = "100"
 * Output: 3
 * Explanation: 69, 88, and 96 are three strobogrammatic numbers.
 */

/*
 * Note:
 * Because the range might be a large number, the low and high numbers are represented as string.
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
public:
    int strobogrammaticInRange(string low, string high) {
        int min_len = low.size(), max_len = high.size();
        int result = 0;
        string item;
        for(int len = min_len; len <= max_len; ++len)
        {
            int left = 0, right = len - 1;
            item.assign(len, '0');
            dfs(left, right, len, low, high, result, item);
        }
        return result;
    }

private:
    vector<char> chars = {'0','1','6','8','9'};
    vector<char> chars_reverse = {'0','1','9','8','6'};

    void dfs(int left, int right, int len, const string& low, const string& high, int& result, string& item)
    {
        int min_len = low.size(), max_len = high.size();

        if(left > right)
        {
            if((len > min_len || item >= low) && (len < max_len || item <= high))
            ++result;
            return;
        }

        if(left == right)
        {
            for(char ch: vector<char>{'0', '1', '8'})
            {
                item[left] = ch;
                if((len > min_len || item >= low) && (len < max_len || item <= high))
                    ++result;
                item[left] = '0';
            }
            return;
        }

        // left < right
        for(int i = 0; i < (int)chars.size(); ++i)
        {
            char ch = chars[i];
            if(left == 0 && ch == '0') continue;
            item[left] = ch;
            item[right] = chars_reverse[i];
            dfs(left + 1, right - 1, len, low, high, result, item);
            item[left] = '0';
            item[right] = '0';
        }
    }
};

// 数位DP模板
class Solution_2 {
public:
    int strobogrammaticInRange(string low, string high) {
        mapping[0] = 0;
        mapping[1] = 1;
        mapping[8] = 8;
        mapping[6] = 9;
        mapping[9] = 6;
        int result = solve(high) - solve(low) + check(high);
        if(result < 0)
            return 0;
        return result;
    }

private:
    unordered_map<int, int> mapping;

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
                break;
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
