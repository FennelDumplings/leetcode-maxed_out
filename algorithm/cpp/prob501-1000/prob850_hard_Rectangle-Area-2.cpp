// prob850: Rectangle Area II

/*
 * We are given a list of (axis-aligned) rectangles.  Each rectangle[i] = [x1, y1, x2, y2] , where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.
 * Find the total area covered by all rectangles in the plane.  Since the answer may be too large, return it modulo 10^9 + 7.
 */

/*
 * Example 1:
 * Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
 * Output: 6
 * Explanation: As illustrated in the picture.
 * Example 2:
 * Input: [[0,0,1000000000,1000000000]]
 * Output: 49
 * Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.
 */

/*
 * Note:
 *
 * 1 <= rectangles.length <= 200
 * rectanges[i].length = 4
 * 0 <= rectangles[i][j] <= 10^9
 * The total area covered by all rectangles will never exceed 2^63 - 1 and thus will fit in a 64-bit signed integer.
 */

#include <vector>
#include <set>
#include <map>

using namespace std;

struct Event
{
    int y_down;
    int y_up;
    bool left;
    Event(int y_down, int y_up, bool left):y_down(y_down),y_up(y_up),left(left){}
};

struct YRange
{
    int y_down, y_up;
    YRange(int d, int u):y_down(d),y_up(u){}
};

struct YRange_BT_Cmp
{
    bool operator()(const YRange& yr1, const YRange& yr2) const
    {
        if(yr1.y_down == yr2.y_down)
            return yr1.y_up < yr2.y_up;
        return yr1.y_down < yr2.y_down;
    }
};

class Solution {
public:
    // unordered_map<int, multiset<int>> left -> y
    int rectangleArea(vector<vector<int>>& rectangles) {
        map<int, vector<Event>> events;
        for(const vector<int>& r: rectangles)
        {
            events[r[0]].push_back(Event(r[1], r[3], true)); // x1 -> y1
            events[r[2]].push_back(Event(r[1], r[3], false)); // x2 -> y2;
        }
        multiset<YRange, YRange_BT_Cmp> y_ranges; // 不带合并的所有 y 区间
        // 枚事件发生时的 x;
        // 计算前一段 (x - prev_x) * (prev_h)
        // 若左，则将对应 y 插入 ys
        // 若右，则从 ys 删除对应 y
        // prev_h = ys.rbegin() - ys.begin()
        auto x_iter = events.begin();
        int prev_x = x_iter -> first;
        for(const Event& e: events[prev_x])
            y_ranges.insert(YRange(e.y_down, e.y_up));
        int prev_h = get_h(y_ranges);
        ++x_iter;
        ll result = 0;
        while(x_iter != events.end())
        {
            int cur_x = x_iter -> first;
            // cout << "x: " << cur_x  << " ; prev_x : " << prev_x << " ; prev_h : " << prev_h << endl;
            result += (ll)(cur_x - prev_x) * prev_h;
            // cout << "y: " ;
            for(const Event& e: events[cur_x])
            {
                // cout << e.y_down << " " << e.y_up << " , ";
                YRange cur(e.y_down, e.y_up);
                if(e.left)
                    y_ranges.insert(cur);
                else
                    y_ranges.erase(y_ranges.find(cur));
            }
            // cout << "]" << endl;
            prev_h = get_h(y_ranges);
            prev_x = cur_x;
            ++x_iter;
        }
        return result % MOD;
    }

private:
    const int MOD = 1e9 + 7;
    using ll = long long;

    int get_h(const multiset<YRange, YRange_BT_Cmp>& y_ranges)
    {
        if(y_ranges.empty()) return 0;
        // cout << "--------------------" << endl;
        auto it = y_ranges.begin();
        int result = it -> y_up - it -> y_down;
        int left = it -> y_up;
        ++it;
        while(it != y_ranges.end())
        {
            if(left < it -> y_up)
            {
                result += it -> y_up - max(left, it -> y_down);
                left = it -> y_up;
            }
            ++it;
        }
        return result;
    }
};
