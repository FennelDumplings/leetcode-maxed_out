// interview05.03: 翻转数位

/*
 * https://leetcode-cn.com/problems/reverse-bits-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int reverseBits(int num) {
        int prev0 = 0, prev1 = 0;
        int ans = 0;
        for(int i = 0; i < 32; ++i)
        {
            int cur = (num >> i) & 1;
            if(cur == 1)
            {
                ans = max(ans, prev1 + 1);
                ++prev0;
                ++prev1;
            }
            else
            {
                ans = max(ans, prev0 + 1);
                prev1 = prev0 + 1;
                prev0 = 0;
            }
        }
        return ans;
    }
};
