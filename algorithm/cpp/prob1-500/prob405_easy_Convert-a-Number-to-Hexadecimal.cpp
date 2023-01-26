// prob405: Convert a Number to Hexadecimal

/*
 * https://leetcode-cn.com/problems/convert-a-number-to-hexadecimal/
 */


#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string toHex(int num) {
        if(num == 0) return "0";
        string result;
        int mask = (1 << 4) - 1;
        unsigned int iter = num;
        while(iter)
        {
            int d = iter & mask;
            result += int2ch(d);
            iter >>= 4;
        }
        reverse(result.begin(), result.end());
        return result;
    }

private:
    int int2ch(int x)
    {
        // 0 <= x <= 15
        if(x < 10)
            return '0' + x;
        x -= 10;
        return 'a' + x;
    }

};
