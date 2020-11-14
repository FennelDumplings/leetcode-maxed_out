// prob980: Find and Replace Pattern

/*
 * https://leetcode-cn.com/problems/find-and-replace-pattern/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        string new_p = get_mapping(pattern);
        vector<string> result;
        for(const string& s: words)
        {
            string new_s = get_mapping(s);
            if(new_s == new_p)
                result.push_back(s);
        }
        return result;
    }

private:
    unordered_map<char, char> mapping;

    string get_mapping(const string& s)
    {
        mapping.clear();
        char iter = 'a';
        for(const char& ch: s)
        {
            if(mapping.count(ch) > 0)
                continue;
            mapping[ch] = iter++;
        }
        string result = s;
        for(char &ch: result)
            ch = mapping[ch];
        return result;
    }
};
