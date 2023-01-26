// prob1342: Number of Steps to Reduce a Number to Zero

/*
 * https://leetcode-cn.com/problems/number-of-steps-to-reduce-a-number-to-zero/
 */

class Solution {
public:
    int numberOfSteps (int num) {
        int ans = 0;
        while(num)
        {
            if(num & 1)
                --num;
            else
                num >>= 1;
            ++ans;
        }
        return ans;
    }
};
