// prob1592: Rearrange Spaces Between Words

/*
 * https://leetcode-cn.com/problems/rearrange-spaces-between-words/
 */


#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string reorderSpaces(string text) {
        int n = text.size();
        int i = 0;
        int cnt = 0;
        vector<string> words;
        while(i < n)
        {
            while(i < n && text[i] == ' ')
            {
                ++cnt;
                ++i;
            }
            if(i == n)
                break;
            int j = i;
            while(j < n && text[j] != ' ')
                ++j;
            words.push_back(text.substr(i, j - i));
            i = j;
        }
        int m = words.size();
        if(m == 1)
        {
            return words[0] + string(cnt, ' ');
        }
        int c = cnt / (m - 1);
        string result;
        for(int i = 0; i < m - 1; ++i)
        {
            result += words[i];
            result += string(c, ' ');
        }
        result += words.back();
        result += string(cnt % (m - 1), ' ');
        return result;
    }
};
