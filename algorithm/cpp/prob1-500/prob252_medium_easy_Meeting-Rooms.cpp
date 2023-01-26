// prob252: Meeting Rooms

/*
 * Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.
 */

/*
 * Example 1:
 * Input: [[0,30],[5,10],[15,20]]
 * Output: false
 * Example 2:
 * Input: [[7,10],[2,4]]
 * Output: true
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n <= 1) return true;
        sort(intervals.begin(), intervals.end());
        int pre_right = intervals[0][1];
        for(int i = 1; i < n; ++i)
        {
            int left = intervals[i][0], right = intervals[i][1];
            if(left < pre_right)
                return false;
            pre_right = right;
        }
        return true;
    }
};
