// prob151: Reverse Words in a String

/*
 * Given an input string, reverse the string word by word.
 */

/*
 * Example 1:
 * Input: "the sky is blue"
 * Output: "blue is sky the"
 * Example 2:
 * Input: "  hello world!  "
 * Output: "world! hello"
 * Explanation: Your reversed string should not contain leading or trailing spaces.
 * Example 3:
 * Input: "a good   example"
 * Output: "example good a"
 * Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
 */

/*
 * Note:
 * A word is defined as a sequence of non-space characters.
 * Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
 * You need to reduce multiple spaces between two words to a single space in the reversed string.
 */

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        if(s.empty()) return "";
        stringstream ss;
        ss << s;
        string word;
        vector<string> words;
        while(ss >> word)
        {
            words.push_back(word);
        }
        int n = words.size();
        string result;
        for(int i = n - 1; i >= 0; --i)
            result += words[i] + ' ';
        if(!result.empty())
            result.pop_back();
        return result;
    }
};
