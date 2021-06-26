// interview17.10: 主要元素

/*
 * https://leetcode-cn.com/problems/find-majority-element-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        if(n == 1) return nums[0];
        int cand = -1;
        int prev = -1;
        int cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(cnt == 0)
            {
                prev = cand;
                cand = nums[i];
                cnt = 1;
                continue;
            }
            if(nums[i] == cand)
                ++cnt;
            else
                --cnt;
        }
        cnt = 0;
        for(int i: nums)
            if(i == cand)
            {
                ++cnt;
                if(cnt > n / 2)
                    return i;
            }
        cnt = 0;
        for(int i: nums)
            if(i == prev)
            {
                ++cnt;
                if(cnt > n / 2)
                    return i;
            }
        return -1;
    }
};
