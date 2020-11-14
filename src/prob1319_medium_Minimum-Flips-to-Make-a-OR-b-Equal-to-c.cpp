// prob1319: Minimum Flips to Make a OR b Equal to c

/*
 * https://leetcode-cn.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/
 */

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int ans = 0;
        for(int i = 0; i < 30; ++i)
        {
            if((c >> i & 1) == 0)
            {
                if(a >> i & 1)
                    ++ans;
                if(b >> i & 1)
                    ++ans;
            }
            else
            {
                if((a >> i & 1) == 0 && (b >> i & 1) == 0)
                    ++ans;
            }
        }
        return ans;
    }
};
