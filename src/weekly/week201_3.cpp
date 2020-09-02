
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

class Solution {
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


