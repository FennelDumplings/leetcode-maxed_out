// prob1403: Minimum Subsequence in Non-Increasing Order

/*
 * https://leetcode-cn.com/problems/minimum-subsequence-in-non-increasing-order/
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int sum = 0;
        for(int i: nums) sum += i;
        vector<int> result;
        int s = 0;
        for(int i: nums)
        {
            s += i;
            result.push_back(i);
            if(s > sum / 2)
                return result;
        }
        return {};
    }
};
