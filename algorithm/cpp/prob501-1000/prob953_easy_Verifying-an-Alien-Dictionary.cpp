// prob953: Verifying an Alien Dictionary

/*
 * https://leetcode-cn.com/problems/verifying-an-alien-dictionary/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        vector<int> mapping;
        for(int i = 0; i < 26; ++i)
        {
            char ch = order[i];
            mapping[ch - 'a'] = i;
        }
        int n = words.size();
        if(n == 1)
            return true;
        string prev = words[0];
        for(char &ch: prev)
            ch = 'a' + mapping[ch - 'a'];
        for(string w: words)
        {
            for(char &ch: w)
                ch = 'a' + mapping[ch - 'a'];
            if(w < prev)
                return false;
            prev = w;
        }
        return true;
    }
};
