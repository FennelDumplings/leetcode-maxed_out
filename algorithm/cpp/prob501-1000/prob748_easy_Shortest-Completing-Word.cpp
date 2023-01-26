// prob748: Shortest Completing Word

/*
 * https://leetcode-cn.com/problems/shortest-completing-word/
 */

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<int> target_cnts(26);
        for(char ch: licensePlate)
        {
            if(ch >= 'A' && ch <= 'Z')
                ch += 'a' - 'A';
            if(ch >= 'a' && ch <= 'z')
                ++target_cnts[ch - 'a'];
        }
        int max_len = -1;
        string result = "";
        for(const string& word: words)
        {
            if(max_len != -1 && (int)word.size() >= max_len)
                continue;
            if(check(target_cnts, word))
            {
                max_len = word.size();
                result = word;
            }
        }
        return result;
    }

private:
    bool check(const vector<int>& target_cnts, const string& word)
    {
        vector<int> cnts(26);
        for(char ch: word)
        {
            if(ch >= 'A' && ch <= 'Z')
                ch += 'a' - 'A';
            if(ch >= 'a' && ch <= 'z')
                ++cnts[ch - 'a'];
        }
        for(int i = 0; i < 26; ++i)
            if(cnts[i] < target_cnts[i])
                return false;
        return true;
    }
};
