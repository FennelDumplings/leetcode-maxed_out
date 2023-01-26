// prob1590: Make Sum Divisible by P

/*
 * https://leetcode-cn.com/problems/make-sum-divisible-by-p/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int all_sum = 0;
        for(int i: nums)
            all_sum = (all_sum + i) % p;
        int gap = all_sum;
        if(gap == 0)
            return 0;
        // mapping: prefix_sum -> 最右边出现的索引
        unordered_map<int, int> mapping;
        mapping[0] = -1;
        int n = nums.size();
        int prefix_sum = 0;
        int ans = n;
        for(int i = 0; i < n; ++i)
        {
            prefix_sum = (prefix_sum + nums[i]) % p;
            int t = (prefix_sum - gap + p) % p;
            if(mapping.count(t))
            {
                int j = mapping[t];
                ans = min(ans, i - j);
            }
            mapping[prefix_sum] = i;
        }
        if(ans == n)
            return -1;
        return ans;
    }
};
