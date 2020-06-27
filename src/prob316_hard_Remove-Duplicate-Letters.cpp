// prob316: Remove Duplicate Letters

/*
 * Given a string which contains only lowercase letters, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
 */

/*
 * Example 1:
 * Input: "bcabc"
 * Output: "abc"
 * Example 2:
 * Input: "cbacdcbc"
 * Output: "acdb"
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        if(s.empty()) return "";
        vector<int> mapping(26); // a~z -> 最右出现位置
        int n = s.size();
        for(int i = 0; i < n; ++i)
            if(mapping[s[i] - 'a'] < i)
                mapping[s[i] - 'a'] = i;
        string result = "";
        vector<bool> used(26, false);
        for(int i = 0; i < n; ++i)
        {
            char ch = s[i];
            if(used[ch - 'a']) continue;
            while(!result.empty() && result.back() > ch && mapping[result.back() - 'a'] > i)
            {
                used[result.back() - 'a'] = false;
                result.pop_back();
            }
            result += ch;
            used[ch - 'a'] = true;
        }
        return result;
    }
};
