// prob1021: Remove Outermost Parentheses

/*
 * https://leetcode-cn.com/problems/remove-outermost-parentheses/
 */

#include <string>

using namespace std;

class Solution {
public:
    string removeOuterParentheses(string S) {
        int cnt_left = 0, cnt_right = 0;
        int n = S.size();
        string result;
        int i = 0;
        while(i < n)
        {
            ++cnt_left;
            int j = i + 1;
            while(j < n && cnt_left > cnt_right)
            {
                if(S[j] == ')')
                    ++cnt_right;
                else
                    ++cnt_left;
                ++j;
            }
            // [i..j-1] 为一个原语
            result += S.substr(i + 1, (j - i - 2));
            i = j;
        }
        return result;
    }
};
