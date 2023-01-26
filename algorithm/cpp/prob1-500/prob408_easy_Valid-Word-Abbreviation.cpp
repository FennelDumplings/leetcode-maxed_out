// prob408: Valid Word Abbreviation

/*
 * https://leetcode-cn.com/problems/valid-word-abbreviation/
 */

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int n = word.size();
        int m = abbr.size();
        int i = 0, j = 0;
        while(i < n && j < m)
        {
            // word[i], abbr[j]
            if(abbr[j] >= '0' && abbr[j] <= '9')
            {
                int r = j + 1;
                while(r < n && abbr[r] >= '0' && abbr[r] <= '9')
                    ++r;
                string str_len = abbr.substr(j, r - j);
                if(str_len.front() == '0')
                    return false;
                stringstream ss;
                ss << str_len;
                int len;
                ss >> len;
                i += len;
                j = r;
            }
            else
            {
                if(abbr[j] != word[i])
                    return false;
                ++i;
                ++j;
            }
        }
        // i >= n 或 j >= m
        return i == n && j == m;
    }
};
