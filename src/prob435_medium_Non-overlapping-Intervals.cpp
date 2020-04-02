// prob435:  Non-overlapping Intervals

/*
 * Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
 */

/*
 * Note:
 * You may assume the interval's end point is always bigger than its start point.
 * Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
 */

/*
 * Example 1:
 * Input: [[1,2],[2,3],[3,4],[1,3]]
 * Output: 1
 * Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
 * Example 2:
 * Input: [[1,2],[1,2],[1,2]]
 * Output: 2
 * Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
 * Example 3:
 * Input: [[1,2],[2,3]]
 * Output: 0
 * Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.empty()) return 0;
        int n = intervals.size();
        if(n == 1) return 0;
        sort(intervals.begin(), intervals.end(), compare);
        int prev = 0;
        int result = 0;
        for(int i = 1; i < n; ++i)
        {
            if(intervals[prev][1] > intervals[i][0]) // prev 与 i 有重叠
            {
                if(intervals[prev][1] > intervals[i][1])
                    prev = i;
                ++result;
            }
            else
            {
                prev = i;
            }
        }
        return result;
    }

private:
    static bool compare(const vector<int>& interval1, const vector<int>& interval2)
    {
        return interval1[0] < interval2[0];
    }
};
