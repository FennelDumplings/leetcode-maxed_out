// prob1638: Count Substrings That Differ by One Character

/*
 * https://leetcode-cn.com/problems/count-substrings-that-differ-by-one-character/
 */

#include <string>

using namespace std;

class Solution {
public:
    int countSubstrings(string s, string t) {
        int n = s.size();
        int m = t.size();
        int ans = 0;
        for(int si = 0; si < n; ++si)
            for(int sj = 0; sj < m; ++sj)
            {
                int i = si, j = sj;
                int diff = 0;
                while(i < n && j < m && diff < 2)
                {
                    if(s[i] != t[j])
                        ++diff;
                    if(diff == 1)
                        ++ans;
                    ++i;
                    ++j;
                }
            }
        return ans;
    }
};
