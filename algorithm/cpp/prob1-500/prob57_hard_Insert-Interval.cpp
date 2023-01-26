// prob57: Insert Interval

/*
 * Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
 * You may assume that the intervals were initially sorted according to their start times.
 */

/*
 * Example 1:
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 * Example 2:
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 * Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if(intervals.empty()) return vector<vector<int> >(1, newInterval);
        int n = intervals.size();
        vector<vector<int> > results;
        int i = 0;
        while(i < n && intervals[i][0] < newInterval[0])
        {
            results.push_back(intervals[i]);
            ++i;
        }
        if(results.empty() || results.back()[1] < newInterval[0])
            results.push_back(newInterval);
        else
            results.back()[1] = max(results.back()[1], newInterval[1]);
        while(i < n)
        {
            if(results.back()[1] < intervals[i][0])
                results.push_back(intervals[i]);
            else
                results.back()[1] = max(results.back()[1], intervals[i][1]);
            ++i;
        }
        return results;
    }
};
