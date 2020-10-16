// prob1576: Replace All ?'s to Avoid Consecutive Repeating Characters'

/*
 * https://leetcode-cn.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/
 */


#include <string>

using namespace std;

class Solution {
public:
    string modifyString(string s) {
        int n = s.size();
        for(int i = 0; i < n; ++i)
        {
            if(s[i] != '?')
                continue;
            for(int j = 0; j < 26; ++j)
            {
                if(i > 0 && s[i - 1] == 'a' + j)
                    continue;
                if(i < n - 1 && s[i + 1] == 'a' + j)
                    continue;
                s[i] = 'a' + j;
                break;
            }
        }
        return s;
    }
};
