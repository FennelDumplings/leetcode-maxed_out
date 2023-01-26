// prob1247: Minimum Swaps to Make Strings Equal

/*
 * https://leetcode-cn.com/problems/minimum-swaps-to-make-strings-equal/
 */

#include <string>

using namespace std;

class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int n = s1.size();
        int cntxy = 0, cntyx = 0;
        for(int i = 0; i < n; ++i)
        {
            if(s1[i] == 'x' && s2[i] == 'y')
                ++cntxy;
            if(s1[i] == 'y' && s2[i] == 'x')
                ++cntyx;
        }
        if((cntxy + cntyx) & 1)
            return -1;
        int ans = 0;
        if(cntxy % 2 == 1)
            ans += 2;
        ans += cntxy / 2;
        ans += cntyx / 2;
        return ans;
    }
};
