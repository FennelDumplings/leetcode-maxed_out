// prob391: Perfect Rectangle

/*
 * Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.
 * Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).
 */

/*
 * Example 1:
 * rectangles = [
 *   [1,1,3,3],
 *   [3,1,4,2],
 *   [3,2,4,4],
 *   [1,3,2,4],
 *   [2,3,3,4]
 * ]
 * Return true. All 5 rectangles together form an exact cover of a rectangular region.
 * Example 2:
 * rectangles = [
 *   [1,1,2,3],
 *   [1,3,2,4],
 *   [3,1,4,2],
 *   [3,2,4,4]
 * ]
 * Return false. Because there is a gap between the two rectangular regions.
 * Example 3:
 * rectangles = [
 *   [1,1,3,3],
 *   [3,1,4,2],
 *   [1,3,2,4],
 *   [3,2,4,4]
 * ]
 * Return false. Because there is a gap in the top center.
 * Example 4:
 * rectangles = [
 *   [1,1,3,3],
 *   [3,1,4,2],
 *   [1,3,2,4],
 *   [2,2,4,4]
 * ]
 * Return false. Because two of the rectangles overlap with each other.
 */

#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

// lc715 的区间模块


class Ranges
{
public:
    bool insert(int left, int right)
    {
        // [left, right)
        // 插入若有 overlap 则返回 true
        IT l, r;
        bool has_overlap = get_overlap_ranges(left, right, l, r);
        if(l != r)
        {
            auto last = r;
            --last;
            left = min(left, l -> first);
            right = max(right, last -> second);
            ranges.erase(l, r);
        }
        ranges[left] = right;
        return has_overlap;
    }

    void remove(int left, int right)
    {
        // [left, right)
        IT l, r;
        get_overlap_ranges(left, right, l, r);
        if(l == r) return;
        auto last = r;
        --last;
        int start = min(left, l -> first);
        int end = max(right, last -> second);
        ranges.erase(l, r);
        if(start < left)
            ranges[start] = left;
        if(end > right)
            ranges[right] = end;
    }

    bool empty()
    {
        return ranges.empty();
    }

    int range_num()
    {
        return ranges.size();
    }

    pair<int, int> span()
    {
        return pair<int, int>(ranges.begin() -> first, ranges.rbegin() -> second);
    }

private:
    using IT = map<int, int>::iterator;
    map<int, int> ranges; // l -> r   [l, r)
    // [l1, r1) 和 [l2, r2) 若 r1 == l2 则也要合并，这是开区间的好处

    bool get_overlap_ranges(int left, int right, IT& l, IT& r)
    {
        // l, r 之间的节点均为有重的区间，不含 r
        l = ranges.upper_bound(left);
        r = ranges.upper_bound(right);
        bool has_overlap = false;
        if(l != ranges.end())
            if(l -> first < right)
            {
                // cout << l -> first << " " << l -> second << " ; " << left << " " << right << endl;
                has_overlap = true;
            }
        if(l != ranges.begin())
        {
            --l;
            if(l -> second > left)
            {
                // cout << l -> first << " " << l -> second << " ; " << left << " " << right << endl;
                has_overlap = true;
            }
            if(l -> second < left)
                ++l;
        }
        return has_overlap;
    }
};

struct Event
{
    int up, down;
    bool left;
    Event(int up, int down, bool left):up(up),down(down),left(left){}
};

struct Event_BT_Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        return e1.left < e2.left; // 右端排前面
    }
};

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        map<int, multiset<Event, Event_BT_Cmp>> mapping; // x -> events
        for(const vector<int>& rec: rectangles)
        {
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            mapping[x1].insert(Event(y2, y1, true));
            mapping[x2].insert(Event(y2, y1, false));
        }
        Ranges ranges;
        bool init = false, finish = false;
        int most_down = 0, most_up = 0;
        for(const auto &item: mapping)
        {
            const multiset<Event, Event_BT_Cmp> &events = item.second;
            for(const Event &e: events)
            {
                if(e.left)
                {
                    // cout << item.first <<  " 插入：" << e.down << " " << e.up << endl;
                    if(ranges.insert(e.down, e.up))
                    {
                        // cout << "有重叠" << endl;
                        return false;
                    }
                }
                else
                {
                    // cout << item.first <<  " 删除：" << e.down << " " << e.up << endl;
                    ranges.remove(e.down, e.up);
                }
            }
            if(ranges.empty())
                finish = true;
            else if(ranges.range_num() > 1)
            {
                // cout << "有横缝隙" << endl;
                return false;
            }
            else
            {
                if(finish)
                {
                    // cout << "有竖缝隙" << endl;
                    return false;
                }
                auto span = ranges.span();
                if(!init)
                {
                    most_down = span.first;
                    most_up = span.second;
                    init = true;
                }
                else
                {
                    if(most_down != span.first || most_up != span.second)
                    {
                        // cout << "一条竖线，但不相等" << endl;
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
