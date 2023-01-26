// interview44: 数字序列中某一位的数字

/*
 * https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/
 */

#include <cmath>
#include <string>

using namespace std;

class Solution {
public:
    int findNthDigit(int n) {
        if(n == 0) return 0;
        int len = 1;
        using ll = long long;
        while(true)
        {
            ll len_all = len * 9 * pow(10, (len - 1));
            if((ll)n <= len_all)
                break;
            ++len;
            n -= len_all;
        }
        // len 位数，从 100..0 开始
        // len = 2 为例子，3,4 属于第二(k = (n + 1) / len)个数 t = 11
        int k = (n - 1) / len; // n 所在数字前面有 k 个数
        int t = pow(10, len - 1) + k;
        n -= k * len;
        return to_string(t)[n - 1] - '0';
    }
};
