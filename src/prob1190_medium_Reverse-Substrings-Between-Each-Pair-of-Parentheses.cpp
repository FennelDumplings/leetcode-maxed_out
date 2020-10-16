// prob1190: Reverse Substrings Between Each Pair of Parentheses

/*
 * https://leetcode-cn.com/problems/reverse-substrings-between-each-pair-of-parentheses/
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();
        return solve(s, 0, n - 1);
    }

private:
    string solve(const string& s, int l, int r)
    {
        if(r < l)
            return "";
        // [l, r] 间找括号
        int i = l;
        string ans;
        while(i <= r)
        {
            int j = i;
            while(j <= r && s[j] != '(')
                ++j;
            ans += s.substr(i, j - i);
            if(j == r)
                break;
            // [i..j-1] 不变
            i = j;
            // i < r && s[i] == '('
            int cnt = 1;
            j = i + 1;
            while(j <= r)
            {
                if(s[j] == '(')
                    ++cnt;
                else if(s[j] == ')')
                    --cnt;
                if(cnt == 0)
                {
                    // [i..j]
                    string part = solve(s, i + 1, j - 1);
                    reverse(part.begin(), part.end());
                    ans += part;
                    break;
                }
                ++j;
            }
            i = j + 1;
        }
        return ans;
    }
};

