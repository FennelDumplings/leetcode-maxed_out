// 1614: Maximum Nesting Depth of the Parentheses

/*
 * https://leetcode-cn.com/problems/maximum-nesting-depth-of-the-parentheses/
 */

#include <string>

using namespace std;

class Solution {
public:
    int maxDepth(string s) {
        int cnt = 0;
        int ans = 0;
        for(char ch: s)
        {
            if(ch == '(')
            {
                ++cnt;
                ans = max(ans, cnt);
            }
            else if(ch == ')')
                --cnt;
        }
        return ans;
    }
};
