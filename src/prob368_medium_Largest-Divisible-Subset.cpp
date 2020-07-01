// prob368: Largest Divisible Subset

/*
 * Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies:
 * Si % Sj = 0 or Sj % Si = 0.
 * If there are multiple solutions, return any subset is fine.
 */
/*
 * Example 1:
 * Input: [1,2,3]
 * Output: [1,2] (of course, [1,3] will also be ok)
 * Example 2:
 * Input: [1,2,4,8]
 * Output: [1,2,4,8]
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.empty()) return {};
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> dp(n, 1); // dp[i] := 以 i 为最大值的最大整除自己
        vector<int> father(n, -1);
        for(int i = 1; i < n; ++i)
        {
            for(int j = 0; j < i; ++j)
            {
                if(nums[i] % nums[j] == 0)
                {
                    if(dp[j] + 1 > dp[i])
                    {
                        dp[i] = max(dp[i], dp[j] + 1);
                        father[i] = j;
                    }
                }
            }
        }
        int iter = 0;
        int max_dp = dp[0];
        for(int i = 1; i < n; ++i)
            if(dp[i] > max_dp)
            {
                max_dp = dp[i];
                iter = i;
            }
        vector<int> result;
        while(iter != -1)
        {
            result.push_back(nums[iter]);
            iter = father[iter];
        }
        return result;
    }
};
