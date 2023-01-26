// interview39: 数组中出现次数超过一半的数字

/*
 * https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cand = -1, cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(cnt == 0)
            {
                cand = nums[i];
                ++cnt;
                continue;
            }
            if(cand == nums[i])
                ++cnt;
            else
                --cnt;
        }
        cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] == cand)
                ++cnt;
            if(cnt > n / 2)
                return cand;
        }
        return -1;
    }
};
