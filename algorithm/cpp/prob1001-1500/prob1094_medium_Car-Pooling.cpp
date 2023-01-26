// prob1094: Car Pooling

/*
 * You are driving a vehicle that has capacity empty seats initially available for passengers.  The vehicle only drives east (ie. it cannot turn around and drive west.)
 *
 * Given a list of trips, trip[i] = [num_passengers, start_location, end_location] contains information about the i-th trip: the number of passengers that must be picked up, and the locations to pick them up and drop them off.  The locations are given as the number of kilometers due east from your vehicle's initial location.
 *
 * Return true if and only if it is possible to pick up and drop off all passengers for all the given trips. 
 */

/*
 * Example 1:
 *
 * Input: trips = [[2,1,5],[3,3,7]], capacity = 4
 * Output: false
 * Example 2:
 *
 * Input: trips = [[2,1,5],[3,3,7]], capacity = 5
 * Output: true
 * Example 3:
 *
 * Input: trips = [[2,1,5],[3,5,7]], capacity = 3
 * Output: true
 * Example 4:
 *
 * Input: trips = [[3,2,7],[3,7,9],[8,3,9]], capacity = 11
 * Output: true
 */

/*
 * Constraints:
 *
 * trips.length <= 1000
 * trips[i].length == 3
 * 1 <= trips[i][0] <= 100
 * 0 <= trips[i][1] < trips[i][2] <= 1000
 * 1 <= capacity <= 100000
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Event
{
    int idx;
    // 右端点排前面，先下
    bool side; // false: 右，true: 左
    int num; // 涉及的乘客数，根据 side 决定是上还是下
    Event(int idx, bool side, int num):idx(idx),side(side),num(num){}
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
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<Event> events;
        for(const vector<int>& trip: trips)
        {
            // trip[0,1,2] : num, start, end
            events.push_back(Event(trip[1], true, trip[0]));
            events.push_back(Event(trip[2], false, trip[0]));
        }
        sort(events.begin(), events.end(), Cmp());
        int sum = 0;
        for(const Event &e : events)
        {
            if(e.side)
                sum += e.num;
            else
                sum -= e.num;
            if(sum > capacity)
                return false;
        }
        return true;
    }
};
