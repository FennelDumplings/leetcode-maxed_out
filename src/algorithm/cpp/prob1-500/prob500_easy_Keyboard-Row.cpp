// prob500: Keyboard Row

/*
 * https://leetcode-cn.com/problems/keyboard-row/
 */

#include <vector>
#include <string>
#include<unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> settings = {
            "qwertyuiop",
            "asdfghjkl",
            "zxcvbnm"
        };
        int diff = 'A' - 'a';
        unordered_map<char, int> mapping;
        for(int i = 0; i < (int)settings.size(); ++i)
            for(char ch: settings[i])
            {
                mapping[ch] = i;
                mapping[ch + diff] = i;
            }
        vector<string> result;
        for(const string& s: words)
        {
            int key = mapping[s[0]];
            bool flag = true;
            for(char ch: s)
                if(mapping[ch] != key)
                {
                    flag = false;
                    break;
                }
            if(flag)
                result.push_back(s);
        }
        return result;
    }
};
