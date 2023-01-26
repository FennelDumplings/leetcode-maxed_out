// prob921: Minimum Add to Make Parentheses Valid

/*
 * https://leetcode-cn.com/problems/minimum-add-to-make-parentheses-valid/
 */

#include <string>

using namespace std;

class Solution {
public:
    int minAddToMakeValid(string S) {
        int n = S.size();
        int left_cnt = 0;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            if(S[i] == '(')
                ++left_cnt;
            else
            {
                --left_cnt;
                if(left_cnt < 0)
                {
                    ++ans;
                    ++left_cnt;
                }
            }
        }
        ans += left_cnt;
        return ans;
    }
};
