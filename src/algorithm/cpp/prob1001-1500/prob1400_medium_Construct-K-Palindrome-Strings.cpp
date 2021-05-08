// prob1400: Construct K Palindrome Strings

/*
 * https://leetcode-cn.com/problems/construct-k-palindrome-strings/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool canConstruct(string s, int k) {
        int n = s.size();
        if(n < k)
            return false;
        vector<int> cnts(26);
        for(const char &ch: s)
        {
            ++cnts[ch - 'a'];
        }
        int c1 = 0;
        for(int i = 0; i< 26; ++i)
            if(cnts[i] & 1)
                ++c1;
        if(c1 > k)
            return false;
        return true;
    }
};
