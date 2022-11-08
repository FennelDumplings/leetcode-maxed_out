// prob8: String to Integer

/*
 * 1. 丢弃开头的空字符
 * 2. 第一个非空字符为有效整数字符(+-数字), 则与后续尽可能多的数字连起来
 * 3. 除有效整数部分之外，后续的字符忽略即可，不应对结果有影响
 * 4. 空串，仅含空字符的串，第一个非空字符不是有效整数字符 -> 不需要进行转换
 * 5. 任何无法有效转换返回 0
 * 6. 爆INT时，根据正负返回 INT_MIN 或者 INT_MAX
 * 7. 仅 ' ' 认为是空字符
 */

#include <string>
#include <climits>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        if(str.empty())
            return 0; // 空串的情况
        int n = str.size();

        int sign = 1;
        int start = 0; // 第一个非空字符的位置
        for(; start < n; ++start)
            if(str[start] != ' ')
                break;
        if(start == n)
            return 0; // 仅含空字符的情况
        if(!is_digit(str[start]) && !is_sign(str[start]))
            return 0; // 第一个非空字符不是有效整数字符的情况
        if(is_sign(str[start]))
        {
            if(str[start] == '-')
                sign = -1;
            ++start;
        }

        int result = 0;
        // 一上来 start 就等于 n 是 +- 号之后紧跟着非数字的情况，不进循环, result 为 0 不变
        while(start < n && is_digit(str[start]))
        {
            int iter = char2int(str[start]);
            if(result > (INT_MAX - iter) / 10)
            {
                if(sign == 1)
                    return INT_MAX;
                else
                    return INT_MIN;
            }
            result = result * 10 + iter; // 这里有可能溢出，以上是处理
            ++start;
        }
        if(sign == 1)
            return result;
        else
            return -result;
    }

private:
    int char2int(const char &c)
    {
        if(c - '0' >= 0 && c - '0' <= 9)
            return c - '0';
        return -1;
    }

    bool is_digit(const char &c)
    {
        return c - '0' >= 0 && c - '0' <= 9;
    }

    bool is_sign(const char &c)
    {
        return (c == '+') || (c == '-');
    }
};

#include <vector>

class Solution_2 {
public:
    int myAtoi(string str) {
        if(str.empty()) return 0;
        int n = str.size();
        int state = 0;
        vector<bool> finals({0, 0, 1});
        vector<vector<int>> transfer({
                {0,  1,  2, -1},
                {-1, -1, 2, -1},
                {-1, -1, 2, -1},
                });

        int sign = 1;
        long long ans = 0;
        for(int i = 0; i < n; ++i)
        {
            state = transfer[state][_make(str[i])];
            if(state < 0)
                return sign * ans;
            if(state == 1 && str[i] == '-')
                sign = -1;
            if(state == 2)
            {
                ans *= 10;
                ans += str[i] - '0';
            }
            if(ans * sign <= INT_MIN)
                return INT_MIN;
            if(ans * sign >= INT_MAX)
                return INT_MAX;
        }
        return sign * ans;
    }

private:
    int _make(const char& c)
    {
        switch(c)
        {
            case ' ': return 0;
            case '+': return 1;
            case '-': return 1;
            default: return _number(c);
        }
    }

    int _number(const char& ch)
    {
        if(ch >= '0' && ch <= '9')
            return 2;
        else
            return 3;
    }
};
