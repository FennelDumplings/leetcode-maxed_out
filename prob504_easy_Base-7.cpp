// prob504: Base 7

/*
 * Given an integer, return its base 7 string representation.
 */

/*
 * Example 1:
 * Input: 100
 * Output: "202"
 * Example 2:
 * Input: -7
 * Output: "-10"
 */

/*
 * Note: The input will be in range of [-1e7, 1e7].
 */

#include <string>

using namespace std;

class Solution {
public:
    string convertToBase7(int num) {
        if(num == 0) return "0";
        string result = "";
        if(num < 0)
        {
            result += '-';
            num = -num;
        }
        int n = 0, p = 7; // p 是 7 的 n + 1 次幂
        while(p <= num)
        {
            p *= 7;
            ++n;
        }
        p /= 7; // p 从 7 的 n + 1 次幂更正为 7 的 n 次幂, 对应七进制数有 n + 1 位
        while(p >= 1)
        {
            int digit = num / p;
            result += '0' + digit;
            num %= p;
            p /= 7;
        }
        return result;
    }
};
