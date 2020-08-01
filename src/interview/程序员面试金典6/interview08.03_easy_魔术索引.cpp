// interview08.03: 魔术索引

/*
 * https://leetcode-cn.com/problems/magic-index-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findMagicIndex(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        for(int i = 0; i < n; ++i)
            if(nums[i] == i)
                return i;
        return -1;
    }
};

// 变种二分
