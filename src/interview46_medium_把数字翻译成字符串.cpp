// 面46: 把数字翻译成字符串

/*
 * 给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。
 * 一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
 */

/*
 * 示例 1:
 * 输入: 12258
 * 输出: 5
 * 解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
 */

/*
 * 提示：
 * 0 <= num < 231
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int translateNum(int num) {
        string num_str = to_string(num);
        int result = 0;
        dfs(num_str, 0, result);
        return result;
    }

private:
    void dfs(const string& num_str, int pos, int& result)
    {
        int n = num_str.size();
        if(pos == n)
        {
            ++result;
            return;
        }
        dfs(num_str, pos + 1, result);
        if(pos + 1 < n && ((num_str[pos] == '2' && num_str[pos + 1] <= '5') || num_str[pos] == '1'))
            dfs(num_str, pos + 2, result);
    }
};
