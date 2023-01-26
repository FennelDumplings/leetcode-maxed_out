// prob1546: Maximum Number of Non-Overlapping Subarrays With Sum Equals Target

/*
 * https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Range
{
    int l, r;
    Range(int l, int r):l(l),r(r){}
};

struct Cmp
{
    bool operator()(const Range& r1, const Range r2) const
    {
        return r1.r < r2.r;
    }
};

class Solution_2 {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();

        unordered_map<int, int> mapping; // sum -> idxs
        mapping[0] = -1;
        int sum = 0;
        vector<Range> ranges;
        for(int i = 0; i < n; ++i)
        {
            sum += nums[i];
            int gap = sum - target;
            if(mapping.count(gap) > 0)
            {
                ranges.push_back(Range(mapping[gap] + 1, i));
            }
            mapping[sum] = i;
        }
        sort(ranges.begin(), ranges.end(), Cmp());
        int ans = 0;
        int right = -1;
        for(const Range &range: ranges)
        {
            if(range.l > right)
            {
                ++ans;
                right = range.r;
            }
        }
        return ans;
    }
};

// DP
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        // dp[i] := [0..i - 1] 上的最大个数 (i >= 1)
        vector<int> dp(n + 1, 0);
        // mapping[sum] 和 sum 出现的最右索引
        unordered_map<int, int> mapping;
        // p[i] := [x..i] 上的区间和为 target 的最大的 x, 不存在为 -1
        vector<int> p(n, -1);
        mapping[0] = -1;
        int sum = 0;
        for(int i = 0; i < n; ++i)
        {
            sum += nums[i];
            // sum = target + gap
            int gap = sum - target;
            if(mapping.count(gap))
                p[i] = mapping[gap] + 1;
            mapping[sum] = i;
        }
        for(int i = 1; i <= n; ++i)
        {
            dp[i] = dp[i - 1];
            if(p[i - 1] != -1)
                dp[i] = max(dp[i], dp[p[i - 1]] + 1);
        }
        return dp[n];
    }
};
