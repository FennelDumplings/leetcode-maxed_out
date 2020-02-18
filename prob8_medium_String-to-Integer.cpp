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
        if(str.empty()) return 0; // 空串的情况
        int n = str.size();

        int sign = 1;
        int start = 0; // 第一个非空字符的位置
        for(; start < n; ++start)
            if(str[start] != ' ')
                break;
        if(start == n) return 0; // 仅含空字符的情况
        if(!is_intchar(str[start])) return 0; // 第一个非空字符不是有效整数字符的情况
        if(is_sign(str[start]))
        {
            if(str[start] == '-')
                sign = -1;
            ++start;
        }

        // const string numbers = "0123456789";
        // for(int i = 0; i <= 9; ++i)
        //     mapping[numbers[i]] = i;

        int result = 0;
        // 一上来 start 就等于 n 是 +- 号之后紧跟着非数字的情况，不进循环, result为0不变
        while(start < n && is_digit(str[start]))
        {
            // int iter = mapping[str[start]];
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
    // unordered_map<char, int> mapping;

    int char2int(const char &c)
    {
        switch(c)
        {
            case '0': return 0;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            case '8': return 8;
            case '9': return 9;
            default: return -1;
        }
    }

    bool is_digit(const char &c)
    {
        switch(c)
        {
            case '0': return true;
            case '1': return true;
            case '2': return true;
            case '3': return true;
            case '4': return true;
            case '5': return true;
            case '6': return true;
            case '7': return true;
            case '8': return true;
            case '9': return true;
            default: return false;
        }
    }

    bool is_sign(const char &c)
    {
        if(c == '+' || c == '-')
            return true;
        else
            return false;
    }

    bool is_intchar(const char &c)
    {
        if(is_digit(c) || is_sign(c))
            return true;
        else
            return false;
    }
};
