// prob291: Word Pattern II

/*
 * Given a pattern and a string str, find if str follows the same pattern.
 * Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.
 */

/*
 * Example 1:
 * Input: pattern = "abab", str = "redblueredblue"
 * Output: true
 * Example 2:
 * Input: pattern = "aaaa", str = "asdasdasdasd"
 * Output: true
 * Example 3:
 * Input: pattern = "aabb", str = "xyzabcxzyabc"
 * Output: false
 */

/*
 * Constraints:
 * You may assume both pattern and str contains only lowercase letters.
 */

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        if(str.empty() && pattern.empty()) return true;
        if(str.empty() || pattern.empty()) return false;
        unordered_map<char, string> char2word;
        unordered_map<string, char> word2char;
        return dfs(pattern, str, 0, 0, char2word, word2char);
    }

private:
    bool dfs(const string& pattern, const string& s, int ls, int lp, unordered_map<char, string>& char2word, unordered_map<string, char>& word2char)
    {
        int n = s.size(), m = pattern.size();
        if(lp == m && ls == n)
            return true;
        else if(ls == n || lp == m)
            return false;
        if(m - lp > n - ls)
            return false;
        char p = pattern[lp];
        // p 此前出现过
        if(char2word.count(p) > 0)
        {
            int len = char2word[p].size();
            if(ls + len <= n && s.substr(ls, len) == char2word[p])
                return dfs(pattern, s, ls + len, lp + 1, char2word, word2char);
            else
                return false;
        }
        // p 未出现过, 需要对应一个此前未出现的词
        for(int i = ls; i < n; ++i)
        {
            int len = i - ls + 1;
            string word = s.substr(ls, len);
            if(word2char.count(word) > 0) // word 此前出现过
                continue;
            char2word[p] = word;
            word2char[word] = p;
            int result = dfs(pattern, s, i + 1, lp + 1, char2word, word2char);
            char2word.erase(char2word.find(p));
            word2char.erase(word2char.find(word));
            if(result)
                return true;
        }
        return false;
    }
};
