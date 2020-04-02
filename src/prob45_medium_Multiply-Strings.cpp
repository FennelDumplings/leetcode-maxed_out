// prob43: Multiply Strings

/*
 * Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.
 */

/*
 * Example 1:
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 * Example 2:
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 */

/*
 * Note:
 * The length of both num1 and num2 is < 110.
 * Both num1 and num2 contain only digits 0-9.
 * Both num1 and num2 do not contain any leading zero, except the number 0 itself.
 * You must not use any built-in BigInteger library or convert the inputs to integer directly.
 */

#include <string>
#include <vector>

using namespace std;

// 朴素思路，时间空间都比较差，能过
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1.empty()) return num2;
        if(num2.empty()) return num1;
        int n = num1.size(), m = num2.size();
        if(n < m) return multiply(num2, num1); // 保证 m < n

        // 一串 m 长与 n 长的数相乘，m 次 n 长的串以一个数相乘，时间 O(MN)
        // return multiply1(num1, num2);
        return multiply2(num1, num2);
    }

    string multiply1(string num1, string num2) {
        int m = num2.size();
        // 先取得 m 个 nx1 的结果，再 m 路求和, 空间 O(MN)
        vector<string> nx1_results(m, "");
        for(int i = 0; i < m; ++i)
        {
            string nx1_result = _multiply_nx1(num1, num2[m - 1 - i]);
            if(nx1_result != "0") _leftshift_k0(nx1_result, i);
            nx1_results[m - 1 - i] = nx1_result;
        }
        string result = _add_m_channels(nx1_results);
        return result;
    }

    string multiply2(string num1, string num2) {
        int m = num2.size();
        // 每次取得 nx1 的结果，都更新一次结果，不用 m 路求和, 空间 O(M+N)
        string result;
        for(int i = 0; i < m; ++i)
        {
            string nx1_result = _multiply_nx1(num1, num2[m - 1 - i]);
            if(nx1_result != "0") _leftshift_k0(nx1_result, i);
            result = _add_2_channels(nx1_result, result);
        }
        return result;
    }

private:
    string _multiply_nx1(const string& num, char x)
    {
        if(x == '0') return "0";
        int n = num.size();
        string result(n, '0');
        char carry = '0';
        // i -> n - 1 - i
        for(int i = 0; i < n; ++i)
        {
            auto result_1x1 = _multiply_1x1(num[n - 1 - i], x);
            auto bit_result = _add_1x1(result_1x1.first, '0', carry);
            result[n - 1 - i] = bit_result.first;
            carry = _add_1x1(result_1x1.second, bit_result.second, '0').first;
        }
        if(carry != '0') result = carry + result;
        return result;
    }

    void _leftshift_k0(string& num, int k)
    {
        // 左移 k 个零
        string k0(k, '0');
        num += k0;
    }

    string _add_m_channels(vector<string>& nx1_results)
    {
        // m 路求和
        string result = "0";
        for(string nx1_result: nx1_results)
            result = _add_2_channels(result, nx1_result);
        return result;
    }

    // leetcode prob415
    string _add_2_channels(string& num1, string& num2)
    {
        // 2 路求和
        int n1 = num1.size(), n2 = num2.size();
        if(n1 < n2) return _add_2_channels(num2, num1); // 保证 n1 > n2
        string result(n1, 0);
        char carry = '0';
        int i;
        // [0..n2..n1]
        // i -> n1 - 1 - i, n2 - 1 - i
        for(i = 0; i < n2; ++i)
        {
            auto add_1x1_result = _add_1x1(num1[n1 - 1 - i], num2[n2 - 1 - i], carry);
            result[n1 - 1 -i] = add_1x1_result.first;
            carry = add_1x1_result.second;
        }
        for(; i < n1; ++i)
        {
            auto add_1x1_result = _add_1x1(num1[n1 - 1 - i], '0', carry);
            result[n1 - 1 - i] = add_1x1_result.first;
            carry = add_1x1_result.second;
        }
        if(carry != '0') result = carry + result;
        return result;
    }

    pair<char, char> _multiply_1x1(const char& a, const char& b)
    {
        int result = _char2int(a) * _char2int(b);
        if(result < 10) return pair<char, char>(_int2char(result), '0');
        else return pair<char, char>(_int2char(result % 10), _int2char(result / 10));
    }

    pair<char, char> _add_1x1(const char& a, const char& b, const char& carry)
    {
        int result = _char2int(a) + _char2int(b) + _char2int(carry);
        if(result < 10) return pair<char, char>(_int2char(result), '0');
        else return pair<char, char>(_int2char(result % 10), _int2char(result / 10));
    }

    int _char2int(const char& a)
    {
        switch(a)
        {
            case('1'): return 1;
            case('2'): return 2;
            case('3'): return 3;
            case('4'): return 4;
            case('5'): return 5;
            case('6'): return 6;
            case('7'): return 7;
            case('8'): return 8;
            case('9'): return 9;
            default: return 0;
        }
    }

    char _int2char(int x)
    {
        switch(x)
        {
            case(1): return '1';
            case(2): return '2';
            case(3): return '3';
            case(4): return '4';
            case(5): return '5';
            case(6): return '6';
            case(7): return '7';
            case(8): return '8';
            case(9): return '9';
            default: return '0';
        }
    }
};

// 优化竖式
// 该算法是通过两数相乘时，乘数某位与被乘数某位相乘，与产生结果的位置的规律来完成。具体规律如下：
// 乘数 num1 位数为 MM，被乘数 num2 位数为 NN， num1 x num2 结果 res 最大总位数为 M+N
// num1[i] x num2[j] 的结果为 tmp(位数为两位，"0x","xy"的形式)，其第一位位于 res[i+j]，第二位位于 res[i+j+1]
// 实际跑的结果与朴素写法稍快
class Solution_2 {
public:
    string multiply(string num1, string num2) {
        if(num1.empty()) return num2;
        if(num2.empty()) return num1;
        int n = num1.size(), m = num2.size();
        if(n < m) return multiply(num2, num1); // 保证 m < n

        string result(m + n, '0');
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                pair<char, char> result_1x1 = _multiply_1x1(num1[i], num2[j]);
                char carry = result_1x1.second;
                pair<char, char> tmp1 = _add_1x1(result_1x1.first, result[i + j + 1], '0');
                result[i + j + 1] = tmp1.first;
                pair<char, char> tmp2 = _add_1x1(tmp1.second, result[i + j], carry);
                result[i + j] = tmp2.first;
                carry = tmp2.second;
                int k = i + j - 1;
                while(carry != '0')
                {
                    pair<char, char> tmp = _add_1x1('0', result[k], carry);
                    result[k] = tmp.first;
                    carry = tmp.second;
                    --k;
                }
            }
        int i;
        for(i = 0; i < m + n; ++i)
            if(result[i] != '0') break;

        if(i == m + n) return "0";
        else
            return result.substr(i, m + n - i);
    }

private:
    pair<char, char> _add_1x1(const char& a, const char& b, const char& carry)
    {
        int result = _char2int(a) + _char2int(b) + _char2int(carry);
        if(result < 10) return pair<char, char>(_int2char(result), '0');
        else return pair<char, char>(_int2char(result % 10), _int2char(result / 10));
    }

    pair<char, char> _multiply_1x1(const char& a, const char& b)
    {
        int result = _char2int(a) * _char2int(b);
        if(result < 10) return pair<char, char>(_int2char(result), '0');
        else return pair<char, char>(_int2char(result % 10), _int2char(result / 10));
    }

    int _char2int(const char& a)
    {
        switch(a)
        {
            case('1'): return 1;
            case('2'): return 2;
            case('3'): return 3;
            case('4'): return 4;
            case('5'): return 5;
            case('6'): return 6;
            case('7'): return 7;
            case('8'): return 8;
            case('9'): return 9;
            default: return 0;
        }
    }

    char _int2char(int x)
    {
        switch(x)
        {
            case(1): return '1';
            case(2): return '2';
            case(3): return '3';
            case(4): return '4';
            case(5): return '5';
            case(6): return '6';
            case(7): return '7';
            case(8): return '8';
            case(9): return '9';
            default: return '0';
        }
    }
};

