// prob1647: Minimum Deletions to Make Character Frequencies Unique

/*
 * https://leetcode-cn.com/problems/minimum-deletions-to-make-character-frequencies-unique/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDeletions(string s) {
        vector<int> cnts(26);
        for(char ch: s)
            ++cnts[ch - 'a'];
        // sort(cnts.begin(), cnts.end());
        int prev = cnts[25];
        int ans = 0;
        for(int i = 24; i >= 0; --i)
        {
            if(cnts[i] >= prev)
            {
                if(prev == 0)
                {
                    ans += cnts[i];
                }
                else
                {
                    ans += cnts[i] - prev + 1;
                    --prev;
                }
            }
            else
                prev = cnts[i];
        }
        return ans;
    }
};
