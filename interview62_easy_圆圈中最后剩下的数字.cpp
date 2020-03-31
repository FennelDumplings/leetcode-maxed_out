// 面62: 圆圈中最后剩下的数字

/*
 * 0,1,,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。
 * 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
 */

/*
 * 示例 1：
 * 输入: n = 5, m = 3
 * 输出: 3
 * 示例 2：
 */

/*
 * 限制：
 * 1 <= n <= 10^5
 * 1 <= m <= 10^6
 */

// 递推法
class Solution {
public:
    int lastRemaining(int n, int m) {
        int idx = 0; // 对应 i = 1
        for(int i = 2; i <= n; ++i)
        {
            idx = (idx + m) % i;
        }
        return idx;
    }
};

// 递推法优化
class Solution {
public:
    int lastRemaining(int n, int m) {
        if (m == 1) return n - 1;
        int last = 0, t = 1;
        for (int i = 2; i <= n; i += t) {
            t = (i - last + m - 3) / (m - 1);
            if (i + t - 1 > n) {
                last += (n - i + 1) * m;
                break;
            }
            (last += t * m) %= (i + t - 1);
        }
        return last;
    }
};

// 数学法
// Ref 具体数学 -- 整数取阶
class Solution {
public:
    int lastRemaining(int n, int m) {
        long D = 1, end = (long)n * (m - 1);
        while (D <= end) {
            D = (m * D + m - 2) / (m - 1);
        }
        return (long)n * m - D;
    }
};
