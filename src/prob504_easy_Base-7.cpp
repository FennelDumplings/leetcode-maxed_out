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
#include <algorithm>

using namespace std;

class Solution {
public:
    string convertToBase7(int num) {
        if(num == 0) return "0";
        bool nega = false;
        if(num < 0)
        {
            nega = true;
            num = -num;
        }
        string result = "";
        int base = 7;
        while(num >= base)
        {
            int r = num % base;
            num /= base;
            result += '0' + r;
        }
        result += '0' + num;
        if(nega) result += '-';
        reverse(result.begin(), result.end());
        return result;
    }
};
