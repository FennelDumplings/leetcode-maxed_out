// interview65: 不用加减乘除做加法

/*
 * https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/
 */

class Solution {
public:
    int add(int a, int b) {
        if(b == 0) return a;
        return add(a ^ b, (unsigned int)(a & b) << 1);
    }
};
