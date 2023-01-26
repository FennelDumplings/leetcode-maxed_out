// prob804: Unique Morse Code Words

/*
 * https://leetcode-cn.com/problems/unique-morse-code-words/
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        mapping = {
            ".-","-...","-.-.","-..",".","..-.","--.","....","..",
            ".---","-.-",".-..","--","-.","---",".--.","--.-",
            ".-.","...","-","..-","...-",".--","-..-","-.--","--.."
        };
        unordered_set<string> setting;
        for(const string &s: words)
        {
            string code = "";
            for(const char &ch: s)
                code += mapping[ch - 'a'];
            setting.insert(code);
        }
        return setting.size();
    }

private:
    vector<string> mapping;
};
