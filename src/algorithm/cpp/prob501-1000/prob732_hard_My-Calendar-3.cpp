// prob732: My Calendar III

/*
 * Implement a MyCalendarThree class to store your events. A new event can always be added.
 * Your class will have one method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
 * A K-booking happens when K events have some non-empty intersection (ie., there is some time that is common to all K events.)
 * For each call to the method MyCalendar.book, return an integer K representing the largest integer such that there exists a K-booking in the calendar.
 * Your class will be called like this: MyCalendarThree cal = new MyCalendarThree(); MyCalendarThree.book(start, end)
 */

/*
 * Example 1:
 * MyCalendarThree();
 * MyCalendarThree.book(10, 20); // returns 1
 * MyCalendarThree.book(50, 60); // returns 1
 * MyCalendarThree.book(10, 40); // returns 2
 * MyCalendarThree.book(5, 15); // returns 3
 * MyCalendarThree.book(5, 10); // returns 3
 * MyCalendarThree.book(25, 55); // returns 3
 * Explanation:
 * The first two events can be booked and are disjoint, so the maximum K-booking is a 1-booking.
 * The third event [10, 40) intersects the first event, and the maximum K-booking is a 2-booking.
 * The remaining events cause the maximum K-booking to be only a 3-booking.
 * Note that the last event locally causes a 2-booking, but the answer is still 3 because
 * eg. [10, 20), [10, 40), and [5, 15) are still triple booked.
 */

/*
 * Note:
 * The number of calls to MyCalendarThree.book per test case will be at most 400.
 * In calls to MyCalendarThree.book(start, end), start and end are integers in the range [0, 10^9].
 */

#include <set>
#include <vector>

using namespace std;

struct Event
{
    int idx;
    bool left;
    Event(int idx, bool left):idx(idx),left(left){}
};

struct Event_BT_Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        if(e1.idx == e2.idx)
            return e1.left < e2.left;
        return e1.idx < e2.idx;
    }
};

class MyCalendarThree {
public:
    MyCalendarThree() {
        events = multiset<Event, Event_BT_Cmp>();
    }

    int book(int start, int end) {
        Event e1(start, true), e2(end, false);
        events.insert(e1);
        events.insert(e2);
        int cnt = 0;
        int max_cnt = 0;
        for(const Event& e: events)
        {
            if(e.left)
            {
                ++cnt;
                max_cnt = max(max_cnt, cnt);
            }
            else
                --cnt;
        }
        return max_cnt;
    }

private:
    multiset<Event, Event_BT_Cmp> events;
};
