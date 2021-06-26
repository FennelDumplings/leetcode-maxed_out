// interview15: 二进制中1的个数

/*
 * https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/
 */

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while(n)
        {
            ans += n % 2;
            n /= 2;
        }
        return ans;
    }
};
