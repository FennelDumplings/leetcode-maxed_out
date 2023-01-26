// prob673: Number of Longest Increasing Subsequence

/*
 * Given an unsorted array of integers, find the number of longest increasing subsequence.
 */

/*
 * Example 1:
 * Input: [1,3,5,4,7]
 * Output: 2
 * Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
 * Example 2:
 * Input: [2,2,2,2,2]
 * Output: 5
 * Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.
 */

/*
 * Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 1;
        vector<int> dp_len(n, 0), dp_cnt(n, 1);
        dp_len[0] = 1;
        for(int i = 1; i < n; ++i)
        {
            for(int k = 0; k < i; ++k)
            {
                if(nums[k] < nums[i])
                {
                    if(dp_len[k] > dp_len[i])
                    {
                        dp_len[i] = dp_len[k];
                        dp_cnt[i] = dp_cnt[k];
                    }
                    else if(dp_len[k] == dp_len[i])
                        dp_cnt[i] += dp_cnt[k];
                }
            }
            dp_len[i] += 1;
        }
        int max_len = 0;
        int max_cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(dp_len[i] > max_len)
            {
                max_len = dp_len[i];
                max_cnt = dp_cnt[i];
            }
            else if(dp_len[i] == max_len)
                max_cnt += dp_cnt[i];
        }
        return max_cnt;
    }
};
