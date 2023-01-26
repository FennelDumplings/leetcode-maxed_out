// prob1347: Minimum Number of Steps to Make Two Strings Anagram

/*
 * https://leetcode-cn.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minSteps(string s, string t) {
        vector<int> cntsa(26);
        for(char ch: s)
            ++cntsa[ch - 'a'];
        int ans = 0;
        for(char ch: t)
        {
            if(cntsa[ch - 'a'] == 0)
                ++ans;
            else
                --cntsa[ch - 'a'];
        }
        return ans;
    }
};
