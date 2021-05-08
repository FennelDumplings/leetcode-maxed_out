// prob916: Word Subsets

/*
 * https://leetcode-cn.com/problems/word-subsets/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        vector<int> char_cnts(26);
        for(const string &b: B)
        {
            vector<int> b_cnts(26);
            for(const char &ch: b)
                ++b_cnts[ch - 'a'];
            for(char ch = 'a'; ch <= 'z'; ++ch)
            {
                int idx = ch - 'a';
                char_cnts[idx] = max(char_cnts[idx], b_cnts[idx]);
            }
        }
        vector<string> result;
        for(const string& a: A)
        {
            vector<int> a_cnts(26);
            for(const char &ch: a)
                ++a_cnts[ch - 'a'];
            bool flag = true;
            for(int i = 0; i < 26; ++i)
                if(a_cnts[i] < char_cnts[i])
                {
                    flag = false;
                    break;
                }
            if(flag)
                result.push_back(a);
        }
        return result;
    }
};
