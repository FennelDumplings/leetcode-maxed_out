// prob1249: Minimum Remove to Make Valid Parentheses

/*
 * https://leetcode-cn.com/problems/minimum-remove-to-make-valid-parentheses/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n = s.size();
        vector<bool> delete_idx(n, false);
        int left_cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(s[i] == '(')
                ++left_cnt;
            else if(s[i] == ')')
            {
                --left_cnt;
                if(left_cnt < 0)
                {
                    delete_idx[i] = true;
                    ++left_cnt;
                }
            }
        }
        int right_cnt = 0;
        for(int i = n - 1; i >= 0; --i)
        {
            if(s[i] == ')')
                ++right_cnt;
            else if(s[i] == '(')
            {
                --right_cnt;
                if(right_cnt < 0)
                {
                    delete_idx[i] = true;
                    ++right_cnt;
                }
            }
        }
        string result;
        for(int i = 0; i < n; ++i)
            if(!delete_idx[i])
                result += s[i];
        return result;
    }
};
