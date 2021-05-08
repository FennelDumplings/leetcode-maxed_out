// prob223: Rectangle Area

/*
 * Find the total area covered by two rectilinear rectangles in a 2D plane.
 * Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
 */

/*
 * Example:
 * Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
 * Output: 45
 */

/*
 * Note:
 * Assume that the total area is never beyond the maximum possible value of int.
 */

#include <algorithm>
#include <vector>

using namespace std;

class Solution_2 {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        long long X = min(C, G) + 0ll - max(A, E);
        long long Y = min(D, H) + 0ll - max(B, F);
        return (C - A) * (D - B) - max(0ll, X) * max(0ll, Y) + (G - E) * (H - F);
    }
};

// ------------------------

using ll = long long;

struct Rectangle
{
    ll x1, y1, x2, y2;
    Rectangle(ll x1, ll y1, ll x2, ll y2):x1(x1),y1(y1),x2(x2),y2(y2){}
};

struct Event
{
    vector<Rectangle> *recs;
    int id; // 所属正方形 id
    int left; // 1 表示左边，-1 表示右边
    Event(vector<Rectangle> *recs, int id, int left):recs(recs),id(id),left(left){}
    ll getx() const
    {
        if(left == 1)
            return (*recs)[id].x1;
        else
            return (*recs)[id].x2;
    }
    bool operator<(const Event& e) const
    {
        return getx() < e.getx();
    }
};

ll union_area(vector<Rectangle>& recs)
{
    int n = recs.size();
    vector<Event> events;
    // 将 y 离散化，每经过一个 x，会有一条边变化，左边则加，右边则减，该变化会对应离散化后的某些区间产生影响。
    vector<int> ys;
    for(int i = 0; i < n; ++i)
    {
        ys.push_back(recs[i].y1);
        ys.push_back(recs[i].y2);
        events.emplace_back(&recs, i, 1);
        events.emplace_back(&recs, i, -1);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(events.begin(), events.end());
    vector<int> cnt((int)ys.size() - 1);
    // 遍历事件
    // 统计事件对应的左边或右边对有几个离散化后的区间产生了影响，并记录。
    // cnt[i] := [ys[i], ys[i+1]) 上的矩形个数
    ll ans = 0;
    for(int i = 0; i < (int)events.size(); ++i)
    {
        ll x = events[i].getx();
        int delta = events[i].left;
        ll y1 = recs[events[i].id].y1;
        ll y2 = recs[events[i].id].y2;
        for(int j = 0; j < (int)cnt.size(); ++j)
        {
            if(y1 <= ys[j] && ys[j] < y2)
                cnt[j] += delta;
        }
        ll len_y = 0;
        for(int j = 0; j < (int)cnt.size(); ++j)
            if(cnt[j] > 0)
                len_y += ys[j + 1] - ys[j];
        if(i + 1 < (int)events.size())
            ans += (events[i + 1].getx() - x) * len_y;
    }
    return ans;
}


class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        vector<Rectangle> recs;
        recs.emplace_back(A, B, C, D);
        recs.emplace_back(E, F, G, H);
        ll ans = union_area(recs);
        return ans;
    }
};
