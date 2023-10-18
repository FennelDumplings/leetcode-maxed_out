// prob301: Remove Invalid Parentheses

/*
 * Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
 * Note: The input string may contain letters other than the parentheses ( and  ).
 */

/*
 * Example 1:
 * Input: "()())()"
 * Output: ["()()()", "(())()"]
 * Example 2:
 * Input: "(a)())()"
 * Output: ["(a)()()", "(a())()"]
 * Example 3:
 * Input: ")("
 * Output: [""]
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// l : 已经往答案中加入的 ( 个数
// r : 已经往答案中加入的 ) 个数
// dl : 需要删除的 (
// dr : 需要删除的 )
// m: 最终匹配对数
//
// 先遍历一遍 s 求 dl, dr, m
//
// 初始 l,r=0, dl,dr,m
// dfs(s, result, result_item, pos, l, r, dl, dr, m)
// 状态转移：
// s[pos] == '('
//     dl > 0 : pos + 1, l, r, dl - 1, dr, m
//     l < m : pos + 1, l + 1, r, dl, dr, m
// s[pos] == ')'
//     dr > 0 : pos + 1, l, r, dl, dr - 1, m
//     r < l : pos + 1, l, r + 1, dl, dr, m
// s[pos] = other
//     pos + 1, l, r, dl, dr, m
// 终止条件
//     pos == n
//     直接加入答案，因为 dfs 过程中把不合法的剪枝掉了
//
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        if(s.empty())
            return vector<string>();
        int dl = 0, dr = 0, m = 0;
        for(char c: s)
        {
            if(c == '(')
            {
                ++dl;
            }
            else if(c == ')')
            {
                if(dl > 0)
                {
                    --dl;
                    ++m;
                }
                else
                    ++dr;
            }
        }
        vector<string> results;
        unordered_set<string> results_set;
        string result_item = "";
        dfs(s, results_set, result_item, 0, 0, 0, dl, dr, m);
        for(string result: results_set)
            results.push_back(result);
        return results;
    }

private:
    void dfs(const string& s, unordered_set<string>& results_set, string& result_item,
            int pos, int l, int r, int dl, int dr, const int m)
    {
        int n = s.size();
        if(pos == n)
        {
            results_set.insert(result_item);
            return;
        }
        if(s[pos] == '(')
        {
            if(dl > 0)
                dfs(s, results_set, result_item, pos + 1, l, r, dl - 1, dr, m);
            if(l < m)
            {
                result_item += s[pos];
                dfs(s, results_set, result_item, pos + 1, l + 1, r, dl, dr, m);
                result_item.pop_back();
            }
        }
        else if(s[pos] == ')')
        {
            if(dr > 0)
                dfs(s, results_set, result_item, pos + 1, l, r, dl, dr - 1, m);
            if(r < l)
            {
                result_item += s[pos];
                dfs(s, results_set, result_item, pos + 1, l, r + 1, dl, dr, m);
                result_item.pop_back();
            }
        }
        else
        {
            result_item += s[pos];
            dfs(s, results_set, result_item, pos + 1, l, r, dl, dr, m);
            result_item.pop_back();
        }
    }
};
