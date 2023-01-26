// prob22: Generate Parentheses

/*
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 */

/*
 *For example, given n = 3, a solution set is:
 * [
 *   "((()))",
 *   "(()())",
 *   "(())()",
 *   "()(())",
 *   "()()()"
 * ]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if(n <= 0) return result;
        string str_item;
        dfs(2 * n, 0, str_item, result, n, n);
        return result;
    }

private:
    void dfs(int str_len, int pos, string &str_item,
            vector<string> &result, int left_num, int right_num)
    {
        // left_num 剩余的左括号个数
        // 已经用了 n - str_item 个左括号
        if(pos == str_len)
        {
            result.push_back(str_item);
            return;
        }
        else
        {
            if(left_num > 0)
            {
                str_item += '(';
                dfs(str_len, pos + 1, str_item, result, left_num - 1, right_num);
                str_item.pop_back();
            }
            if(left_num < right_num)
            {
                str_item += ')';
                dfs(str_len, pos + 1, str_item, result, left_num, right_num - 1);
                str_item.pop_back();
            }
        }
    }
};
