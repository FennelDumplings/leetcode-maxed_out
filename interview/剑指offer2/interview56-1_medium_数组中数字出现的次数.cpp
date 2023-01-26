// interview56-1: 数组中数字出现的次数

/*
 * https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int x = 0;
        for(int num: nums) x ^= num;
        int k = 0;
        while(x)
        {
            if(x & 1)
                break;
            ++k;
            x >>= 1;
        }
        int x1 = 0, x2 = 0;
        for(int num: nums)
        {
            if((num >> k) & 1)
                x1 ^= num;
            else
                x2 ^= num;
        }
        return {x1, x2};
    }
};
