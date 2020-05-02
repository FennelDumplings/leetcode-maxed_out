// 20200502
// 2. 改变一个整数能得到的最大差值

/*
 * 给你一个整数 num 。你可以对它进行如下步骤恰好 两次 ：
 * 选择一个数字 x (0 <= x <= 9).
 * 选择另一个数字 y (0 <= y <= 9) 。数字 y 可以等于 x 。
 * 将 num 中所有出现 x 的数位都用 y 替换。
 * 得到的新的整数 不能 有前导 0 ，得到的新整数也 不能 是 0 。
 * 令两次对 num 的操作得到的结果分别为 a 和 b 。
 * 请你返回 a 和 b 的 最大差值 。
 */

/*
 * 示例 1：
 * 输入：num = 555
 * 输出：888
 * 解释：第一次选择 x = 5 且 y = 9 ，并把得到的新数字保存在 a 中。
 * 第二次选择 x = 5 且 y = 1 ，并把得到的新数字保存在 b 中。
 * 现在，我们有 a = 999 和 b = 111 ，最大差值为 888
 * 示例 2：
 * 输入：num = 9
 * 输出：8
 * 解释：第一次选择 x = 9 且 y = 9 ，并把得到的新数字保存在 a 中。
 * 第二次选择 x = 9 且 y = 1 ，并把得到的新数字保存在 b 中。
 * 现在，我们有 a = 9 和 b = 1 ，最大差值为 8
 * 示例 3：
 * 输入：num = 123456
 * 输出：820000
 * 示例 4：
 * 输入：num = 10000
 * 输出：80000
 * 示例 5：
 * 输入：num = 9288
 * 输出：8700
 */

/*
 * 提示：
 * 1 <= num <= 10^8
 */

#include <sstream>
#include <string>

using namespace std;

class Solution {
public:
    int maxDiff(int num) {
        // 先找从右到左第一个不是 9 的，将其变为 9
        // 若第一个数字不是 1 则将其变为 1，否则从第二个数字开始，找到第一个不是 0 的
        if(num < 10) return 8;
        string str_min = to_string(num);
        string str_max = str_min;
        int n = str_min.size();
        char target = '9';
        for(int i = 0; i < n; ++i)
        {
            char cur = str_max[i];
            if(cur != '9')
            {
                target = cur;
                break;
            }
        }
        for(char &c: str_max)
            if(c == target)
                c = '9';
        int m1;
        stringstream ss;
        ss << str_max;
        ss >> m1;

        if(str_min[0] != '1')
        {
            target = str_min[0];
            for(char &c: str_min)
                if(c == target)
                    c = '1';
        }
        else
        {
            target = '0';
            for(int i = 1; i < n; ++i)
            {
                char cur = str_min[i];
                if(cur != '0' && cur != '1')
                {
                    target = cur;
                    break;
                }
            }
            for(char &c: str_min)
                if(c == target)
                    c = '0';
        }
        int m2;
        stringstream ss2;
        ss2 << str_min;
        ss2 >> m2;
        return m1 - m2;
    }
};
