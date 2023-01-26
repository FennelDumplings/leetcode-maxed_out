// prob400: Nth Digit

/*
 * Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...
 */

/*
 * Note:
 * n is positive and will fit within the range of a 32-bit signed integer (n < 231).
 */

/*
 * Example 1:
 * Input:
 * 3
 * Output:
 * 3
 * Example 2:
 * Input:
 * 11
 * Output:
 * 0
 * Explanation:
 * The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
 */

#include <cmath>
#include <string>

using namespace std;

// 1~9: 9 个，  共 9 * 1 位
// 10~99: 共 90 个，共 90 * 2 位
// 100 ~999 : 共 900 个，共 900 * 3 位
// 给定 n,
// 1. 先确定目标数字(result)对应的数是多少(target), 由总位数，得对应数字是几位数
// 2. 确定这个数 target
// 3. 确定 result 是 target 中的第几位数
class Solution {
public:
    int findNthDigit(int n) {
        // 计算该数字由几位数字组成，由1位：digits = 1；2位：digits = 2...
        long base = 9, digits = 1;
        while (n - base * digits > 0){
            n -= base * digits;
            base *= 10;
            digits++;
        }

        // 计算真实代表的数字是多少
        int idx = n % digits;  // 注意由于上面的计算，n现在表示digits位数的第n个数字
        if(idx == 0) idx = digits;
        long number = 1;
        for (int i = 1;i < digits; i++)
            number *= 10;
        number += (idx == digits) ? n / digits - 1 : n / digits;

        // 从真实的数字中找到我们想要的那个数字
        for (int i = idx; i < digits; i++) number /= 10;
        return number % 10;
    }
};

// 另一种写法
class Solution_2 {
public:
    int findNthDigit(int n) {
        n -= 1;
        for(long digits = 1; digits < 11; ++digits)
        {
            int first_num = pow(10, digits - 1);
            if (n < 9 * first_num * digits)
            {
                return int(to_string(first_num + n / digits)[n % digits]) - '0';
            }
            n -= 9 * first_num * digits;
        }
        return 0;
    }
};
