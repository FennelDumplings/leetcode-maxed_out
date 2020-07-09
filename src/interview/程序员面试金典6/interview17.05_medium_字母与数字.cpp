// interview17.05: 字母与数字

/*
 * https://leetcode-cn.com/problems/find-longest-subarray-lcci/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
        if(array.empty()) return {};
        int n = array.size();
        if(n < 2) return {};
        unordered_map<int, int> mapping;
        mapping[0] = -1;
        // idx = mapping[sum]
        int sum = 0;
        int max_len = -1, max_left_idx = n;
        for(int i = 0; i < n; ++i)
        {
            char cur = array[i][0];
            if(cur >= '0' && cur <= '9')
                ++sum;
            else
                --sum;
            // 当前和为 sum ，要找此前是否出现过 sum
            // 即 gap = sum - target = sum
            if(mapping.count(sum) == 0)
                mapping[sum] = i;
            else
            {
                int idx = mapping[sum];
                int len = i - idx;
                if(len > max_len)
                {
                    max_len = len;
                    max_left_idx = idx;
                }
                else if(len == max_len && idx < max_left_idx)
                    max_left_idx = idx;
            }
        }
        vector<string> result;
        for(int i = max_left_idx + 1; i <= max_left_idx + max_len; ++i)
            result.push_back(array[i]);
        return result;
    }
};
