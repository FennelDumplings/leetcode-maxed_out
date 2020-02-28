// prob415: Add Strings

/*
 * Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.
 */

/*
 * Note:
 * The length of both num1 and num2 is < 5100.
 * Both num1 and num2 contains only digits 0-9.
 * Both num1 and num2 does not contain any leading zero.
 * You must not use any built-in BigInteger library or convert the inputs to integer directly.
 */

#include <string>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        return _add_2_channels(num1, num2);
    }

private:
    string _add_2_channels(string& num1, string& num2)
    {
        int n1 = num1.size(), n2 = num2.size();
        if(n1 < n2) return _add_2_channels(num2, num1); // 保证 n1 > n2
        string result(n1, 0);
        char carry = '0';
        int i;
        // [0..n2..n1]
        // i -> n1 - 1 - i, n2 - 1 - i
        for(i = 0; i < n2; ++i)
        {
            auto add_11_result = _add_11(num1[n1 - 1 - i], num2[n2 - 1 - i], carry);
            result[n1 - 1 -i] = add_11_result.first;
            carry = add_11_result.second;
        }
        for(; i < n1; ++i)
        {
            auto add_11_result = _add_11(num1[n1 - 1 - i], '0', carry);
            result[n1 - 1 - i] = add_11_result.first;
            carry = add_11_result.second;
        }
        if(carry != '0') result = carry + result;
        return result;
    }

    pair<char, char> _add_11(const char& a, const char& b, const char& carry)
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
