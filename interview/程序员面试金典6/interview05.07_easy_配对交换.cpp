// interview05.07: 配对交换

/*
 * https://leetcode-cn.com/problems/exchange-lcci/
 */

class Solution {
public:
    int exchangeBits(int num) {
        int ans = 0;
        for(int i = 0; i < 16; ++i)
        {
            ans |= ((num >> (i * 2)) & 1) << (i * 2 + 1);
            ans |= ((num >> (i * 2 + 1)) & 1) << (i * 2);
        }
        return ans;
    }
};
