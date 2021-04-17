// prob1017: Convert to Base -2

/*
 * https://leetcode-cn.com/problems/convert-to-base-2/
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string baseNeg2(int N) {
        if(N == 0) return "0";
        string result = "";
        int base = -2;
        while(N)
        {
            int digit = abs(N) % abs(base);
            result += '0' + digit;
            N -= digit;
            N /= base;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
