// interview56-2: 数组中数字出现的次数 II

/*
 * https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for(int i = 0; i <= 31; ++i)
        {
            int cnt = 0;
            for(int num: nums)
                if((num >> i) & 1)
                    ++cnt;
            if(cnt % 3 == 1)
                ans |= (1 << i);
        }
        return ans;
    }
};
