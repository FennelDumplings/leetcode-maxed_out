// prob759: Employee Free Time

/*
 * We are given a list schedule of employees, which represents the working time for each employee.
 *
 * Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.
 *
 * Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.
 *
 * (Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.
 */

/*
 * Example 1:
 *
 * Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
 * Output: [[3,4]]
 * Explanation: There are a total of three employees, and all common
 * free time intervals would be [-inf, 1], [3, 4], [10, inf].
 * We discard any intervals that contain inf as they aren't finite.
 * Example 2:
 *
 * Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
 * Output: [[5,6],[7,9]]
 */

/*
 * Constraints:
 *
 * 1 <= schedule.length , schedule[i].length <= 50
 * 0 <= schedule[i].start < schedule[i].end <= 10^8
 */

#include <vector>
#include <algorithm>

using namespace std;

class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

struct Event
{
    int idx;
    bool side; // false: 左，true 右
    Event(int idx, bool side):idx(idx),side(side){}
};
\
struct Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        if(e1.idx == e2.idx)
            return e1.side < e2.side;
        return e1.idx < e2.idx;
    }
};

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        int n_person = schedule.size();
        vector<Event> events;
        for(int i = 0; i < n_person; ++i)
        {
            vector<Interval> &ranges = schedule[i];
            int n_range = ranges.size();
            for(int j = 0; j < n_range; ++j)
            {
                events.push_back(Event(ranges[j].start, false));
                events.push_back(Event(ranges[j].end, true));
            }
        }
        sort(events.begin(), events.end(), Cmp());
        int n_event = events.size();
        int sum = 0;
        vector<Interval> result;
        for(int i = 0; i < n_event; ++i)
        {
            Event e = events[i];
            if(e.side)
                --sum;
            else
                ++sum;
            if(sum == 0)
            {
                if(i + 1 < n_event)
                {
                    result.push_back(Interval(e.idx, events[i + 1].idx));
                }
            }
        }
        return result;
    }
};
