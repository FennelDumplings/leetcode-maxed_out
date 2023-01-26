// prob1229: Meeting Scheduler

/*
 * Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration, return the earliest time slot that works for both of them and is of duration duration.
 * If there is no common time slot that satisfies the requirements, return an empty array.
 * The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.  
 * It is guaranteed that no two availability slots of the same person intersect with each other. That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either start1 > end2 or start2 > end1.
 */

/*
 * Example 1:
 * Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
 * Output: [60,68]
 * Example 2:
 * Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
 * Output: []
 */

/*
 * Constraints:
 * 1 <= slots1.length, slots2.length <= 10^4
 * slots1[i].length, slots2[i].length == 2
 * slots1[i][0] < slots1[i][1]
 * slots2[i][0] < slots2[i][1]
 * 0 <= slots1[i][j], slots2[i][j] <= 10^9
 * 1 <= duration <= 10^6 
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Event
{
    int idx;
    bool side; // 右: false，左: true;
    Event(int idx, bool side):idx(idx),side(side){}
};

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
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        vector<Event> events;
        for(const vector<int>& range: slots1)
        {
            events.push_back(Event(range[0], true));
            events.push_back(Event(range[1], false));
        }
        for(const vector<int>& range: slots2)
        {
            events.push_back(Event(range[0], true));
            events.push_back(Event(range[1], false));
        }
        sort(events.begin(), events.end(), Cmp());
        int start = 0;
        int sum = 0; // 左端点个数
        for(const Event &e: events)
        {
            if(!e.side)
            {
                --sum;
                if(sum == 1)
                {
                    int len = e.idx - start;
                    if(len >= duration)
                        return {start, start + duration};
                }
            }
            else
            {
                ++sum;
                if(sum == 2)
                    start = e.idx;
            }
        }
        return {};
    }
};
