// prob1540: Can Convert String in K Moves

/*
 * https://leetcode-cn.com/problems/can-convert-string-in-k-moves/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        int ns = s.size(), nt = t.size();
        if(ns != nt)
            return false;
        vector<int> cnts(26);
        for(int i = 0; i < ns; ++i)
            ++cnts[(t[i] + 26 - s[i]) % 26];
        for(int t = 0; t < 26; ++t)
        {
            if(t > 0 && cnts[t] > 0)
            {
                int r = (cnts[t] - 1) * 26 + t;
                if(r > k)
                    return false;
            }
        }
        return true;
    }
};
