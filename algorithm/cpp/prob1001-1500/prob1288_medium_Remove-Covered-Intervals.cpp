// prob1288: Remove Covered Intervals

/*
 * Given a list of intervals, remove all intervals that are covered by another interval in the list. Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.
 * After doing so, return the number of remaining intervals.
 */

/*
 * Example 1:
 * Input: intervals = [[1,4],[3,6],[2,8]]
 * Output: 2
 * Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
 */

/*
 * Constraints:
 *
 * 1 <= intervals.length <= 1000
 * 0 <= intervals[i][0] < intervals[i][1] <= 10^5
 * intervals[i] != intervals[j] for all i != j
 */

#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// 平衡树
struct Range
{
    int left;
    int right;
    Range(int l, int r):left(l),right(r){}
};

struct Cmp
{
    bool operator()(const Range& r1, const Range& r2) const
    {
        if(r1.left == r2.left)
            return r1.right > r2.right;
        return r1.left < r2.left;
    }
};

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        set<Range, Cmp> ranges;
        for(const vector<int>& range: intervals)
            ranges.insert(Range(range[0], range[1]));
        auto it = ranges.begin();
        int max_right = -1;
        while(it != ranges.end())
        {
            if(it -> right <= max_right)
                it = ranges.erase(it);
            else
            {
                max_right = it -> right;
                ++it;
            }
        }
        return ranges.size();
    }
};
