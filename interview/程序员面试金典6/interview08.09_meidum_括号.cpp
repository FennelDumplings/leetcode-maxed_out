// interview08.09: 括号

/*
 * https://leetcode-cn.com/problems/bracket-lcci/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if(n == 0) return {};
        vector<string> result;
        string item;
        dfs(n, item, result, 0);
        return result;
    }

private:
    void dfs(int n, string& item, vector<string>& result, int left_cnt)
    {
        int len = item.size();
        if(len == n * 2)
        {
            result.push_back(item);
            return;
        }
        if(len + left_cnt < 2 * n)
        {
            item += '(';
            dfs(n, item, result, left_cnt + 1);
            item.pop_back();
        }
        if(left_cnt > 0)
        {
            item += ')';
            dfs(n, item, result, left_cnt - 1);
            item.pop_back();
        }
    }
};
