// interview05.02: 二进制数转字符串

/*
 * https://leetcode-cn.com/problems/bianry-number-to-string-lcci/
 */

#include <string>
#include <sstream>

using namespace std;

// 乘二取整
// res初始化为"0."
// 在满足位数要求的情况下，当num大于0时，循环
// 先将num乘以2，将乘积赋值给num
// 取num的个位（0或1），将对应的字符加入res的末尾
// 截取num的小数部分，作为num的新值
// 最后判断，当num为0时（即res已经精确地表达了num），返回res
// 否则，返回"ERROR"

class Solution {
public:
    string printBin(double num) {
        const double eps = 1e-10;
        if(num < eps || num + eps > 1)
            return "ERROR";
        string result = "0.";
        int w = 2;
        while(w <= 32 && num > eps)
        {
            num *= 2;
            result += to_string((int)num);
            num -= (int)num;
            ++w;
        }
        if(num < eps)
            return result;
        else
            return "ERROR";
    }
};
