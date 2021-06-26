// interview16.10: 生存人数

/*
 * https://leetcode-cn.com/problems/living-people-lcci/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Event
{
    int idx;
    int kind;
    Event(int idx, int kind):idx(idx),kind(kind){}
    bool operator<(const Event& e) const
    {
        if(idx == e.idx)
            return kind < e.kind;
        return idx < e.idx;
    }
};

class Solution {
public:
    int maxAliveYear(vector<int>& birth, vector<int>& death) {
        if(birth.empty()) return 0;
        int n = birth.size();
        vector<Event> events;
        for(int i = 0; i < n; ++i)
        {
            events.push_back(Event(birth[i], 0));
            events.push_back(Event(death[i], 1));
        }
        sort(events.begin(), events.end());
        int ans = -1;
        int max_sum = 0;
        int sum = 0;
        for(const Event &e: events)
        {
            if(e.kind == 0)
                ++sum;
            else
                --sum;
            if(sum > max_sum)
            {
                max_sum = sum;
                ans = e.idx;
            }
        }
        return ans;
    }
};
