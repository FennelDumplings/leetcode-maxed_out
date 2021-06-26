// interview05.06: 整数转换

/*
 * https://leetcode-cn.com/problems/convert-integer-lcci/
 */

class Solution {
public:
    int convertInteger(int A, int B) {
        int ans = 0;
        for(int i = 0; i < 32; ++i)
            if(((A >> i) ^ (B >> i)) & 1)
                ++ans;
        return ans;
    }
};
