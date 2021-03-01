// prob218: The Skyline Problem

/*
 * https://leetcode-cn.com/problems/the-skyline-problem/
 */

/*
 * Notes:
 * The number of buildings in any input list is guaranteed to be in the range [0, 10000].
 * The input list is already sorted in ascending order by the left x position Li.
 * The output list must be sorted by the x position.
 * There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
 */

#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Event
{
    int h; // 所属区间的高度
    int side; // 所属区间的端点 false-左; true-右
    int idx; // 端点的 idx
    Event(int h, int side, int idx):h(h),side(side),idx(idx){}
};

struct Event_Sort_Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        if(e1.idx == e2.idx && e1.side == e2.side)
        {
            if(!e1.side)
                return e1.h > e2.h; // 均为左端点，高的在前面
            else
                return e1.h < e2.h; // 均为右端点，矮的在前面
        }
        if(e1.idx == e2.idx)
            return e1.side < e2.side; // 左端点排前面
        return e1.idx < e2.idx;
    }
};

struct Event_BT_Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        return e1.h < e2.h;
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // [Li, Ri, Hi]
        vector<Event> events;
        for(const vector<int>& range: buildings)
        {
            events.push_back(Event(range[2], false, range[0]));
            events.push_back(Event(range[2], true, range[1]));
        }
        sort(events.begin(), events.end(), Event_Sort_Cmp());
        multiset<Event, Event_BT_Cmp> active_ranges;
        int max_h = 0;
        vector<vector<int> > result;
        for(const Event& e: events)
        {
            if(!e.side) // 左端点
            {
                active_ranges.insert(e);
                if(e.h > max_h)
                {
                    max_h = e.h;
                    result.push_back(vector<int>{e.idx, max_h});
                }
            }
            else // 右端点
            {
                auto it = active_ranges.upper_bound(e);
                --it;
                it = active_ranges.erase(it);
                if(e.h == max_h)
                {
                    if(active_ranges.empty())
                    {
                        max_h = 0;
                        result.push_back(vector<int>{e.idx, max_h});
                    }
                    else
                    {
                        --it;
                        if(it -> h < max_h)
                        {
                            max_h = it -> h;
                            result.push_back(vector<int>{e.idx, max_h});
                        }
                    }
                }
            }
        }
        return result;
    }
};

