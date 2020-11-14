// prob1256: Encode Number

/*
 * https://leetcode-cn.com/problems/encode-number/
 */

#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    string encode(int num) {
        int l = 0, c = 0;
        while(c + pow(2, l) < num + 1)
        {
            c += pow(2, l);
            ++l;
        }
        int ans = num - c;
        if(ans == 0)
            return string(l, '0');
        int len_ans = floor(log2(ans)) + 1;
        string leading_zeros(l - len_ans, '0');
        string result;
        while(ans)
        {
            result += (ans & 1) + '0';
            ans >>= 1;
        }
        reverse(result.begin(), result.end());
        return leading_zeros + result;
    }
};
