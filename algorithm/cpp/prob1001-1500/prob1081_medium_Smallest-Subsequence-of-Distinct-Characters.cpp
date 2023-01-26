// prob1081: Smallest Subsequence of Distinct Characters

/*
 * Return the lexicographically smallest subsequence of text that contains all the distinct characters of text exactly once.
 */

/*
 * Example 1:
 * Input: "cdadabcc"
 * Output: "adbc"
 * Example 2:
 * Input: "abcd"
 * Output: "abcd"
 * Example 3:
 * Input: "ecbacba"
 * Output: "eacb"
 * Example 4:
 * Input: "leetcode"
 * Output: "letcod"
 */

/*
 * Constraints:
 * 1 <= text.length <= 1000
 * text consists of lowercase English letters.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string smallestSubsequence(string text) {
        if(text.empty()) return "";
        int n = text.size();
        if(n == 1) return text;
        vector<int> cnts(26);
        for(const char& ch: text)
            ++cnts[ch - 'a'];
        string result = "";
        vector<bool> used(26, false);
        for(const char& ch: text)
        {
            --cnts[ch - 'a'];
            if(used[ch - 'a'])
                continue;
            while(!result.empty() && result.back() > ch && cnts[result.back() - 'a'] > 0)
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
