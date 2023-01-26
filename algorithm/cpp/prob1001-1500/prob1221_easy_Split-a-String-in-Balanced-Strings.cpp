// prob1221: Split a String in Balanced Strings

/*
 * https://leetcode-cn.com/problems/split-a-string-in-balanced-strings/
 */

#include <string>

using namespace std;

class Solution {
public:
    int balancedStringSplit(string s) {
        int cnt = 0;
        int ans = 0;
        for(char &ch: s)
        {
            if(ch == 'L')
                ++cnt;
            else
                --cnt;
            if(cnt == 0)
                ++ans;
        }
        return ans;
    }
};
