// prob67: Add Binary

/*
 * Given two binary strings, return their sum (also a binary string).
 * The input strings are both non-empty and contains only characters 1 or 0.
 */

/*
 * Example 1:
 * Input: a = "11", b = "1"
 * Output: "100"
 * Example 2:
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        int m = a.size();
        int n = b.size();
        if(m > n) return addBinary(a, string(m - n, '0') + b);
        if(m < n) return addBinary(string(n - m, '0') + a, b);
        // a 和 b 的长度相等
        mapping['0'] = 0;
        mapping['1'] = 1;
        string result;
        char carry = '0';
        for(int i = m - 1; i >= 0; --i)
        {
            char iter_a = a[i], iter_b = b[i];
            pair<char, char> bit_result = bitadd(iter_a, iter_b, carry);
            result = bit_result.first + result;
            carry = bit_result.second;
        }
        if(carry == '1')
            result = '1' + result;
        return result;
    }

private:
    pair<char, char> bitadd(char a, char b, char carry)
    {
        int sum = mapping[a] + mapping[b] + mapping[carry];
        if(sum == 0) return pair<char, char>('0', '0');
        if(sum == 1) return pair<char, char>('1', '0');
        if(sum == 2) return pair<char, char>('0', '1');
        if(sum == 3) return pair<char, char>('1', '1');
        return pair<char, char>('0', '0');
    }

    unordered_map<char, int> mapping;
};
