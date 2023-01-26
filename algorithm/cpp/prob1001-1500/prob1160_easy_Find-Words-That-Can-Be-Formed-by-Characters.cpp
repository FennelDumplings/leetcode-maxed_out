// prob1160: Find Words That Can Be Formed by Characters

/*
 * You are given an array of strings words and a string chars.
 * A string is good if it can be formed by characters from chars (each character can only be used once).
 * Return the sum of lengths of all good strings in words.
 */

/*
 * Example 1:
 * Input: words = ["cat","bt","hat","tree"], chars = "atach"
 * Output: 6
 * Explanation:
 * The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
 * Example 2:
 * Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
 * Output: 10
 * Explanation:
 * The strings that can be formed are "hello" and "world" so the answer is 5 + 5 = 10.
 */

/*
 * Note:
 * 1 <= words.length <= 1000
 * 1 <= words[i].length, chars.length <= 100
 * All strings contain lowercase English letters only.
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        vector<int> cnts(26, 0);
        for(const char &ch: chars)
            ++cnts[ch - 'a'];
        vector<int> word_cnts(26);
        int result = 0;
        for(const string& word: words)
        {
            word_cnts.assign(26, 0);
            bool flag = true;
            for(const char &ch: word)
            {
                ++word_cnts[ch - 'a'];
                if(cnts[ch - 'a'] < word_cnts[ch - 'a'])
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
                result += word.size();
        }
        return result;
    }
};


