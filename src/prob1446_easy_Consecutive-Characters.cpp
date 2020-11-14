// probh1446: Consecutive Characters

/*
 * https://leetcode-cn.com/problems/consecutive-characters/
 */

#include <string>

using namespace std;

class Solution {
public:
    int maxPower(string s) {
        int n = s.size();
        int i = 0;
        int ans = 0;
        while(i < n)
        {
            char ch = s[i];
            int j = i + 1;
            while(j < n && s[j] == ch)
                ++j;
            ans = max(ans, j - i);
            i = j;
        }
        return ans;
    }
};
