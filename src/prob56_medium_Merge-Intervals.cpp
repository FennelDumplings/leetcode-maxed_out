// prob56: Merge Intervals

/*
 * Given a collection of intervals, merge all overlapping intervals.
 */

/*
 * Example 1:
 * Input: [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
 * Example 2:
 * Input: [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty()) return vector<vector<int> >();
        int n = intervals.size();
        if(n == 1) return intervals;
        sort(intervals.begin(), intervals.end(), compare);
        vector<vector<int> > results;
        int left, right;
        int i = 0;
        do{
            left = intervals[i][0], right = intervals[i][1];
            ++i;
            while(i < n && intervals[i][0] <= right)
            {
                right = max(right, intervals[i][1]);
                ++i;
            }
            results.push_back(vector<int>({left, right}));
        }while(i < n);
        return results;
    }

private:
    static bool compare(const vector<int>& interval1, const vector<int>& interval2)
    {
        return interval1[0] < interval2[0];
    }
};

// 更好的写法
class Solution_2 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty()) return vector<vector<int> >();
        int n = intervals.size();
        if(n == 1) return intervals;
        sort(intervals.begin(), intervals.end(), compare);
        vector<vector<int> > results;
        for(const auto& interval: intervals)
        {
            if(results.empty() || interval[0] > results.back()[1])
                results.push_back(interval);
            else
                results.back()[1] = max(results.back()[1], interval[1]);
        }
        return results;
    }

private:
    static bool compare(const vector<int>& interval1, const vector<int>& interval2)
    {
        return interval1[0] < interval2[0];
    }
};
