// prob1272: Remove Interval

/*
 * Given a sorted list of disjoint intervals, each interval intervals[i] = [a, b] represents the set of real numbers x such that a <= x < b.
 * We remove the intersections between any interval in intervals and the interval toBeRemoved.
 * Return a sorted list of intervals after all such removals.
 */

/*
 * Example 1:
 * Input: intervals = [[0,2],[3,4],[5,7]], toBeRemoved = [1,6]
 * Output: [[0,1],[6,7]]
 * Example 2:
 * Input: intervals = [[0,5]], toBeRemoved = [2,3]
 * Output: [[0,2],[3,5]]
 */

/*
 * Constraints:
 * 1 <= intervals.length <= 10^4
 * -10^9 <= intervals[i][0] < intervals[i][1] <= 10^9
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int>> result;
        for(const vector<int>& range: intervals)
        {
            if(toBeRemoved[1] < range[0] || range[1] < toBeRemoved[0])
            {
                result.push_back(range);
                continue;
            }
            if(range[0] < toBeRemoved[0])
                result.push_back({range[0], toBeRemoved[0]});
            if(toBeRemoved[1] < range[1])
                result.push_back({toBeRemoved[1], range[1]});
        }
        sort(result.begin(), result.end());
        return result;
    }
};
