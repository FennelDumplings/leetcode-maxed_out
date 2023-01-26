// prob824: Goat Latin

/*
 * https://leetcode-cn.com/problems/goat-latin/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string toGoatLatin(string S) {
        int n = S.size();
        int i = 0;
        while(i < n && S[i] == ' ')
            ++i;
        string result;
        int idx = 1;
        while(i < n)
        {
            int j = i;
            while(j < n && S[j] != ' ')
                ++j;
            string word;
            if(check(S[i]))
            {
                word = S.substr(i, j - i);
                word += "ma";
            }
            else
            {
                word = S.substr(i + 1, j - i - 1);
                word += S[i];
                word += "ma";
            }
            word += string(idx, 'a');
            result += word + ' ';
            i = j;
            while(i < n && S[i] == ' ')
                ++i;
            ++idx;
        }
        result.pop_back();
        return result;
    }

private:
    bool check(char ch)
    {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
    }
};
