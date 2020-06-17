// prob253: Meeting Rooms II

/*
 * Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
 */

/*
 * Example 1:
 *
 * Input: [[0, 30],[5, 10],[15, 20]]
 * Output: 2
 * Example 2:
 *
 * Input: [[7,10],[2,4]]
 * Output: 1
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Event
{
    int idx;
    int kind; // 0左1右
    Event(int idx, int kind):idx(idx),kind(kind){}
};

struct Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        if(e1.idx == e2.idx)
            return e1.kind > e2.kind; // 右排前面
        return e1.idx < e2.idx;
    }
};

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n < 2) return n;
        vector<Event> events;
        for(int i = 0; i < n; ++i)
        {
            events.push_back(Event(intervals[i][0], 0));
            events.push_back(Event(intervals[i][1], 1));
        }
        sort(events.begin(), events.end(), Cmp());
        int n_event = events.size();
        int sum = 0;
        int result = 0;
        for(int i = 0; i < n_event; ++i)
        {
            if(events[i].kind == 0)
                ++sum;
            if(events[i].kind == 1)
                --sum;
            result = max(result, sum);
        }
        return result;
    }
};
